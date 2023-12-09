#include "UniquePtr.hpp"

template <typename T>
my_unique_ptr<T>::my_unique_ptr(T* ptr) : ptr(ptr) {}

template <typename T>
my_unique_ptr<T>::my_unique_ptr(my_unique_ptr<T>&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
}

template <typename T>
my_unique_ptr<T>::~my_unique_ptr() {
    delete ptr;
}

template <typename T>
T* my_unique_ptr<T>::release() {
    auto released = ptr;
    ptr = nullptr;
    return released;
}

template <typename T>
void my_unique_ptr<T>::reset(T* new_ptr) {
    auto old_ptr = ptr;
    ptr = new_ptr;
    delete old_ptr;
}

template <typename T>
T* my_unique_ptr<T>::get() {
    return ptr;
}

template <typename U, typename... Args>
my_unique_ptr<U> make_my_unique_personal(Args... args) {
    return my_unique_ptr<U>(new U(std::forward<Args>(args)...));
}