//
// Created by Robin on 2021-05-30.
//
#pragma once
namespace Impact {

    typedef uint16_t ptr_primitive;

    template<class C>
    class Container {
    public:
        virtual C* at(const std::size_t& ptr) = 0;
        virtual void delete_entry(const std::size_t& ptr) = 0;
    };

    /**
     * Generic pointer object to an instance in a global data structure.
     * Deleting the pointer will also delete the reference, so be careful.
     * @tparam C
     */
    template<class C>
    struct pointer {
    public:
        pointer(ptr_primitive ptr, Container<C>* container) : ref(ptr), p_container(container) {}
        C* operator->() {
            if (!p_container) return nullptr;
            return p_container->at(ref);
        }
        ~pointer() {
            if (p_container) {
                p_container->delete_entry(this->ref);
                p_container = nullptr;
            }
        }
        pointer(const pointer<C>& other) = delete;
        pointer(pointer<C>&& other) : ref(other.ref), p_container(other.p_container) {
            other.p_container = nullptr;
        }
        pointer<C>& operator=(const pointer<C>& other) = delete;
        pointer<C>& operator=(pointer<C>&& other) {
            if (ref == other.ref) {
                return *this;
            }
            if (p_container) {
                p_container->delete_entry(ref);
            }
            ref = other.ref;
            p_container = other.p_container;
        }
    private:
        ptr_primitive ref;
        Container<C>* p_container;
    };
}