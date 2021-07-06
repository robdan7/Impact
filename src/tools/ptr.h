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

    template<class C>
    struct ref {
        template<typename... Args>
        ref(Args&&... args) : object(std::forward<Args>(args)...) {}
        uint16_t counter = 0;
        C* operator->() {
            return &this->object;
        }
        C object;
        ptr_primitive self_reference = 0;
        Container<ref<C>>* p_container = nullptr;
    };

    /**
     * Generic pointer object to an instance in a global data structure.
     * Deleting the pointer will also delete the reference, so be careful.
     * @tparam C
     */
    template<class C>
    struct private_ptr {
    public:
        template<typename... Args>
        private_ptr(Args&&... args, Container<ref<C>>* container) {

        }
        private_ptr(ptr_primitive ptr, Container<ref<C>>* container) : ref(ptr), p_container(container) {}
        C* operator->() {
            if (!p_container) return nullptr;
            return p_container->at(ref);
        }
        ~private_ptr() {
            if (p_container) {
                p_container->delete_entry(this->ref);
                p_container = nullptr;
            }
        }
        private_ptr(const private_ptr<C>& other) = delete;
        private_ptr(private_ptr<C>&& other) : ref(other.ref), p_container(other.p_container) {
            other.p_container = nullptr;
        }
        private_ptr<C>& operator=(const private_ptr<C>& other) = delete;
        private_ptr<C>& operator=(private_ptr<C>&& other) {
            if (ref == other.ref && p_container == other.p_container) {
                return *this;
            }
            if (p_container) {
                p_container->delete_entry(ref);
            }
            ref = other.ref;
            p_container = other.p_container;
            other.p_container = nullptr;
            other.ref = 0;
            return *this;
        }
    private:
        ptr_primitive ref = 0;
        Container<C>* p_container = nullptr;
    };

    template<class C>
    struct reference {
    public:
        reference(ptr_primitive ptr, Container<C>* container) : ref(ptr), p_container(container){

        }
        ~reference() {
            if (p_container && this->counter == 1) {
                p_container->delete_entry(this->ref);
            } else {
                this->counter--;
            }
        }
    private:
        uint32_t counter = 0;
        ptr_primitive  ref = 0;
        Container<C>* p_container = nullptr;
    };
}