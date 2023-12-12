#include "SharedPtr.hpp"

template <typename T>
my_shared_ptr<T>::my_shared_ptr() : ptr(nullptr), block(nullptr) {}

template <typename T>
my_shared_ptr<T>::my_shared_ptr(T* ptr_) : ptr(ptr_), block(new ControlBlock<T>(1)) {}

template <typename T>
my_shared_ptr<T>::my_shared_ptr(const my_shared_ptr<T>& other) : ptr(other.ptr), block(other.block) {
    block->count += 1;
}

template <typename T>
my_shared_ptr<T>::my_shared_ptr(my_shared_ptr<T>&& other) noexcept : ptr(other.ptr), block(other.block) {
    other.ptr = nullptr;
    other.block = nullptr;
}

template <typename T>
my_shared_ptr<T>::~my_shared_ptr() {
    if (block) {
        block->count -= 1;
        if (block->count == 0) {
            ptr->~T();
            delete ptr;
            delete block;
            ptr = nullptr;
        }
    }
}

template <typename T>
T* my_shared_ptr<T>::get() {
    return ptr;
}

template <typename T, typename... Args>
my_shared_ptr<T> make_shared_personal(Args... args) {
    return my_shared_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
ControlBlock<T>::ControlBlock(size_t c) : count(c) {}
