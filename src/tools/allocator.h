#pragma once
#ifdef max
#undef max
#endif
#include <limits>
#include <mutex>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include "ptr.h"

namespace Impact {
	class I_Allocator {
	public:

	protected:
		I_Allocator() = default;

		template<class T, typename... Args>
		static T* alloc_header(std::size_t size, Args&&... args) {
			T* alloc = (T*)std::malloc(size + sizeof(T));
			//ORVOX_ASSERT(alloc, "BAD_ALLOC");

			if constexpr (std::is_aggregate_v<T>) {
				new(alloc) T{ std::forward<Args>(args)... };
			}
			else {
				new(alloc) T(std::forward<Args>(args)...);
			}

			return alloc;
		}
	};

	/**
	 * Allocator with a custom memory address length.
	 * @tparam size_t
	 */
	template<class size_t>
	class Allocator : public I_Allocator {
	public:
		~Allocator() = default;
	protected:
		Allocator() : I_Allocator() {}
	};

	template<typename size_type, class T>
	class Same_allocator : public Allocator<size_type> {
		friend I_Allocator;
		friend Allocator<size_type>;
	public:
		static Same_allocator* Create() {
			std::size_t max_index = ((std::size_t)1) << 8 * sizeof(size_type);
			std::size_t offset = 0;
			if constexpr (sizeof(T) > sizeof(size_type)) {
				offset = 1;
			}
			else {
				offset = 1 + sizeof(size_type);
			}
			return I_Allocator::alloc_header<Same_allocator<size_type, T>>(max_index * (offset + sizeof(T)), offset);
		}

		void Destroy() {
			this->m_mutex.lock();
			for (std::size_t i = 1, k = 0; k < this->m_size && i < ((std::size_t)1) << (8 * sizeof(size_type)); ++i) {
				uint8_t* p = nullptr;
				uint8_t valid_byte = false;

				p = (uint8_t*)((i)*this->m_object_size + this->m_start_address);

				valid_byte = *p;
				if (valid_byte) {
					(*((T*)(p + 1))).~T();
					k++;
				}
			}
			this->m_mutex.unlock();
			std::free(this);
		}

		T& operator[](size_type index) {
			this->m_mutex.lock();
			uint8_t* p = nullptr;
			uint8_t valid_byte = false;

			p = (uint8_t*)((index + 1) * this->m_object_size + this->m_start_address);

			valid_byte = *p;
			if (!valid_byte) {
				this->m_mutex.unlock();
				//ORVOX_ERROR("Asked for null value");
				throw std::invalid_argument("Asked for null value");
			}
			else {
				this->m_mutex.unlock();
				return *((T*)(p + 1));
			}
		}

		T& at(size_type index) {
			(*this)[index];
		}

		template<typename... Args>
		size_type alloc(Args... args) {
			this->m_mutex.lock();

			if (!this->available()) {
				//ORVOX_ERROR("BAD ALLOC");
			}
			uint8_t* obj_pointer = nullptr;
			std::size_t index = 1;

			if (!this->m_freelist) {
				/// There are no empty slots in the allocated area. Resize the allocated portion.
				//auto max_size = (((std::size_t)1) << 8*sizeof(size_t))-1;
				if (this->m_size == std::numeric_limits<size_type>::max()) {
					/// No more space!
					this->m_mutex.unlock();
					throw std::bad_alloc();
				}

				obj_pointer = this->m_empty_pointer;
				this->m_empty_pointer += this->m_object_size;

				index = ((std::size_t)obj_pointer - this->m_start_address) / this->m_object_size;
			}
			else {
				/// There is a delete_entry slot somewhere in the pool. Take it and run away.
				index = this->m_freelist;
				obj_pointer = (uint8_t*)(index * this->m_object_size + this->m_start_address);
				this->m_freelist = *(size_type*)(obj_pointer + 1);
			}

			*obj_pointer = true;
			this->m_size++;
			this->m_mutex.unlock();

			if constexpr (std::is_aggregate_v<T>) {
				new((T*)((uint8_t*)obj_pointer + m_offset)) T{ std::forward<Args>(args)... };
			}
			else {
				new((T*)((uint8_t*)obj_pointer + m_offset)) T(std::forward<Args>(args)...);
			}

			return (size_type)(index - 1);
		}

		size_type push(const T& arg) {
            this->m_mutex.lock();

            if (!this->available()) {
                //ORVOX_ERROR("BAD ALLOC");
            }
            uint8_t* obj_pointer = nullptr;
            size_type index = 1;

            if (!this->m_freelist) {
                /// There are no empty slots in the allocated area. Resize the allocated portion.
                //auto max_size = (((std::size_t)1) << 8*sizeof(size_t))-1;
                if (this->m_size == std::numeric_limits<size_type>::max()) {
                    /// No more space!
                    this->m_mutex.unlock();
                    throw std::bad_alloc();
                }

                obj_pointer = this->m_empty_pointer;
                this->m_empty_pointer += this->m_object_size;

                index = ((std::size_t)obj_pointer - this->m_start_address) / this->m_object_size;
            }
            else {
                /// There is a delete_entry slot somewhere in the pool. Take it and run away.
                index = this->m_freelist;
                obj_pointer = (uint8_t*)(index * this->m_object_size + this->m_start_address);
                this->m_freelist = *(size_type*)(obj_pointer + 1);
            }

            *obj_pointer = true;
            this->m_size++;
            this->m_mutex.unlock();

            if constexpr (std::is_aggregate_v<T>) {
                *((T*)((uint8_t*)obj_pointer + m_offset)) = arg;
            }
            else {
                *((T*)((uint8_t*)obj_pointer + m_offset)) = arg;
            }

            return index - 1;
		}

		void free(const size_type& index) {
			auto obj_pointer = (uint8_t*)((index + 1) * this->m_object_size + this->m_start_address);
			//ORVOX_ASSERT(*obj_pointer, "Asked for null value");
			this->m_mutex.lock();
			((T*)(obj_pointer + 1))->~T();
			*obj_pointer = false;
			*((size_type*)(obj_pointer + 1)) = this->m_freelist;

			this->m_freelist = index + 1;
			this->m_size--;
			this->m_mutex.unlock();
		}

		bool available() const {
			return this->m_size < std::numeric_limits<size_type>::max();
		}

		bool is_empty() const {
			return this->m_size;
		}

		bool has_entry(const size_type& index) const {
			this->m_mutex.lock();
			uint8_t* p = nullptr;
			uint8_t valid_byte = false;

			p = (uint8_t*)((index + 1) * this->m_object_size + this->m_start_address);

			valid_byte = *p;
			this->m_mutex.unlock();
			return valid_byte;
		}

		bool has_entry(const size_type&& index) const {
			this->m_mutex.lock();
			uint8_t* p = nullptr;
			uint8_t valid_byte = false;

			p = (uint8_t*)((index + 1) * this->m_object_size + this->m_start_address);

			valid_byte = *p;
			this->m_mutex.unlock();
			return valid_byte;
		}

		size_t size() {
			return this->m_size;
		}

	protected:
		Same_allocator(std::size_t offset) : m_offset(offset), Allocator<size_type>() {
			this->m_object_size = sizeof(T) + this->m_offset;
			this->m_start_address = (std::size_t)(&this->m_empty_pointer + 1);

			this->m_empty_pointer = (uint8_t*)(&this->m_empty_pointer + 1);
			std::memset(this->m_empty_pointer, 0, sizeof(T) + 1);
			this->m_empty_pointer += 1 + sizeof(T);
		}

		mutable std::mutex m_mutex;
		std::size_t m_object_size = 1;
		std::size_t m_offset = 1;
		std::size_t m_start_address;
		size_type m_freelist = 0;
		size_type m_size = 0;

		uint8_t* m_empty_pointer;
	};

	template<int page_t>
	class I_page_storage {
	public:

		std::size_t size() const {
			return this->m_size;
		}

	protected:
		[[nodiscard]] virtual size_t page(const size_t& index) const {
			return index / (((uint32_t)1 << 8 * page_t) - 1);
		}
		[[nodiscard]] virtual size_t offset(const size_t& index) const {
			return index % (((uint32_t)1 << 8 * page_t) - 1);
		}
		std::size_t m_size = 0;
	};

	/**
	 *  Arena locator for the same type of object.
	 * @tparam page_t - number of bytes reserved to pages.
	 * @tparam offset_t
	 * @tparam T
	 */
	template<int page_t, typename offset_t, class T>
	class Same_arena_allocator : public I_page_storage<page_t>, public Container<T> {
	public:
		Same_arena_allocator() = default;

		T& operator[](const std::size_t& index) {
			const std::size_t page = this->page(index);
			const auto offset = (offset_t)this->offset(index);
			return (*this->m_index[page])[offset];
		}

		T* at(const std::size_t& index) override {
			const std::size_t page = this->page(index);
            const auto offset = (offset_t)this->offset(index);
			return &(*this->m_index[page])[offset];
		}


		template<typename... Args>
		std::size_t alloc(Args&&... args) {
			for (std::size_t i = 0; i < sizeof(this->m_index); ++i) {
				if (this->m_index[i] == nullptr) {
					this->m_index[i] = Same_allocator<offset_t, T>::Create();
				}
				if (this->m_index[i]->available()) {
					this->m_size++;
					return this->m_index[i]->alloc(std::forward<Args>(args)...) + i * ((std::size_t)1 << (8 * page_t));
				}
			}

			//ORVOX_ERROR("BAD ALLOC");
			return 0;
		}

		std::size_t push(const T& arg) {
            for (std::size_t i = 0; i < sizeof(this->m_index); ++i) {
                if (this->m_index[i] == nullptr) {
                    this->m_index[i] = Same_allocator<offset_t, T>::Create();
                }
                if (this->m_index[i]->available()) {
                    this->m_size++;
                    return this->m_index[i]->push(arg) + i * ((size_t)1 << (8 * page_t));
                }
            }

            //ORVOX_ERROR("BAD ALLOC");
            return 0;
		}

		void delete_entry(const std::size_t& index) override {
			const std::size_t page = this->page(index);
			const auto offset = (offset_t)this->offset(index);
			//ORVOX_ASSERT(this->m_index[page], "Index out of range");
			this->m_index[page]->free(offset);
			this->m_size--;
		}

		bool has_entry(const std::size_t&& index) const {
			const std::size_t page = this->page(index);
			const std::size_t offset = this->offset(index);

			if (this->m_index[page] == nullptr) {
				return false;
			}
			return this->m_index[page]->has_entry(offset);
		}

		bool has_entry(const std::size_t& index) const {
			const std::size_t page = this->page(index);
			const std::size_t offset = this->offset(index);

			if (this->m_index[page] == nullptr) {
				return false;
			}
			return this->m_index[page]->has_entry(offset);
		}

	private:
		Same_allocator<offset_t, T>* m_index[(uint32_t)1 << (8 * page_t)] = { nullptr };
	};

	/**
	 * Array with smaller contiguous chunks of memory. Adding more elements does not reallocate
	 * the internal storage.
	 * @tparam page_t
	 * @tparam offset_t
	 * @tparam T
	 */
	template<int page_t, typename offset_t, class T>
	class Pool_array : public I_page_storage<page_t> {
	public:
		~Pool_array() {
			for (T*& container : this->m_pages) {
				delete[] container;
			}
		}
		T& operator[](const std::size_t& index) {
			const std::size_t page = this->page(index);
			const std::size_t offset = this->offset(index);
			auto& item = this->m_pages[page][offset];
			return item;
		}

		T& operator[](const std::size_t&& index) {
			const std::size_t page = this->page(index);
			const std::size_t offset = this->offset(index);
			return this->m_pages[page][offset];
		}

		const T& operator[](const std::size_t& index) const {
			const std::size_t page = this->page(index);
			const std::size_t offset = this->offset(index);
			return this->m_pages[page][offset];
		}

		template<typename... Args>
		void emplace(const std::size_t& index, Args... args) {
			auto page = this->page(index);
			auto offset = this->offset(index);

			if (this->m_page_sizes[page] == (uint32_t)1 << (8 * page_t)) {
				//ORVOX_ERROR("Page is out of range");
			}
			else if (this->m_pages[page] == nullptr) {
				T* new_page = (T*)std::calloc(((uint32_t)1 << (8 * sizeof(offset_t))), sizeof(T));
				//T* new_page = new T[((uint32_t)1<< (8*sizeof(offset_t)))];

				//ORVOX_ASSERT(new_page, "BAD ALLOC");
				this->m_pages[page] = new_page;

				this->m_n_of_pages++;
			}
			if constexpr (std::is_aggregate_v<T>) {
				new(&this->m_pages[page][offset]) T{ std::forward<Args>(args)... };
			}
			else {
				new(&this->m_pages[page][offset]) T(std::forward<Args>(args)...);
			}

			this->m_page_sizes[page] ++;
			this->m_size++;
		}

		void push(const std::size_t& index, const T& arg) {
			auto page = this->page(index);
			auto offset = this->offset(index);

			if (this->m_page_sizes[page] == (uint32_t)1 << (8 * page_t)) {
				//ORVOX_ERROR("Page is out of range");
			}
			else if (this->m_pages[page] == nullptr) {
				void* new_page = std::calloc(((uint32_t)1 << (8 * sizeof(offset_t))), sizeof(T));
				//ORVOX_ASSERT(new_page, "BAD ALLOC");
				this->m_pages[page] = (T*)new_page;
				this->m_n_of_pages++;
			}
			this->m_pages[page][offset] = arg;

			this->m_page_sizes[page] ++;
			this->m_size++;
		}

		/**
		 *
		 * @param page - Page index
		 * @return
		 */
		bool has_page(const std::size_t page) const {
			return  this->m_pages[page] != nullptr;
		}

		/**
		 *
		 * @param index - Element index
		 * @return
		 */
		bool has_page_indexed(const std::size_t index) const {
			return this->m_pages[this->page(index)] != nullptr;
		}

		bool not_null(std::size_t index, const T& null_value) const {
			return this->has_page_indexed(index) && this[index] != null_value;
		}

		void free(const std::size_t& index) {
			auto page = this->page(index);
			auto offset = this->offset(index);
			//ORVOX_ASSERT(this->m_pages[page], "Index out of range");
			this->m_pages[page][offset].~T();
			this->m_page_sizes[page] --;

			if (this->m_page_sizes[page] == 0) {
				delete this->m_pages[page];
				this->m_pages[page] = nullptr;
				this->m_n_of_pages--;
			}
			this->m_size--;
		}

		std::size_t n_pages() const {
			return this->m_n_of_pages;
		}

	protected:
		size_t page(const size_t& index) const override {
			return index / (((uint32_t)1 << 8 * page_t));
		}
		size_t offset(const size_t& index) const override {
			return index % (((uint32_t)1 << 8 * page_t));
		}
	private:
		uint32_t m_n_of_pages = 0;
		T* m_pages[(uint32_t)1 << (8 * page_t)] = { nullptr };
		std::size_t m_page_sizes[(uint32_t)1 << (8 * page_t)] = { 0 };
	};

	template<int page_t, typename offset_t, class T>
	class pool_stack {
	public:
		template<typename... Args>
		std::size_t emplace(Args... args) {
			this->m_pool.emplace(this->m_pool.size(), std::forward<Args>(args)...);
			return this->size() - 1;
		}

		std::size_t push(const T& arg) {
			this->m_pool.push(this->m_pool.size(), arg);
			return this->size() - 1;
		}

		T& operator[](const std::size_t& index) {
			return this->m_pool[index];
		};
		T& operator[](const std::size_t&& index) {
			return this->m_pool[index];
		};

		const T& operator[](const std::size_t& index) const {
			return this->m_pool[index];
		};
		const T& operator[](const std::size_t&& index) const {
			return this->m_pool[index];
		};

		void pop() {
			//ORVOX_ASSERT(this->m_pool.size(), "Pool size is zero");
			this->m_pool.free(this->m_pool.size() - 1);
		}

		void collapse(const std::size_t& index) {
			if (index == this->m_pool.size() - 1) {
				this->pop();
			}
			else {
				this->m_pool[index] = std::move(this->m_pool[this->m_pool.size() - 1]);
				this->m_pool.free(this->m_pool.size() - 1);
			}
		}

		std::size_t size() const {
			return this->m_pool.size();
		}
	private:
		Pool_array<page_t, offset_t, T> m_pool;
	};
}
