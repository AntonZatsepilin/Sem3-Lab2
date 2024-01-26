#include "UniquePtr.hpp"
namespace zatsep {
template <class T, class... Args>
typename std::enable_if<!std::is_array<T>::value, UniquePtr<T>>::type make_unique(
    Args &&...args) {  // make_unique for non-array types
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename std::enable_if<std::is_array<T>::value, UniquePtr<T>>::type make_unique(
    std::size_t size) {  // make_unique for array types
    return UniquePtr<T>(new typename std::remove_extent<T>::type[size]());
}

template <class T>
inline UniquePtr<T>::UniquePtr() noexcept : ptr_(nullptr) {}

template <class T>
inline UniquePtr<T[]>::UniquePtr() noexcept : ptr_(nullptr) {}

template <class T>
inline UniquePtr<T>::UniquePtr(T *ptr) noexcept : ptr_(ptr) {}

template <class T>
inline UniquePtr<T[]>::UniquePtr(T *ptr) noexcept : ptr_(ptr) {}

template <class T>
inline UniquePtr<T>::UniquePtr(UniquePtr &&other) noexcept : ptr_(other.release()) {}

template <class T>
inline UniquePtr<T[]>::UniquePtr(UniquePtr &&other) noexcept : ptr_(other.release()) {}

template <class T>
inline UniquePtr<T>::~UniquePtr() {
    delete ptr_;
}

template <class T>
inline UniquePtr<T[]>::~UniquePtr() {
    delete[] ptr_;
}

template <class T>
inline UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr<T> &&other) noexcept {  // move assignment
    if (this != &other) reset(other.release());
    return *this;
}

template <class T>
inline UniquePtr<T[]> &UniquePtr<T[]>::operator=(UniquePtr<T[]> &&other) noexcept {  // move assignment for arrays
    if (this != &other) reset(other.release());
    return *this;
}

template <class T>
inline UniquePtr<T> &UniquePtr<T>::operator=(std::nullptr_t) noexcept {  // assignment from nullptr
    reset(nullptr);
    return *this;
}

template <class T>
inline UniquePtr<T[]> &UniquePtr<T[]>::operator=(std::nullptr_t) noexcept {  // assignment from nullptr for arrays
    reset(nullptr);
    return *this;
}

template <class T>
inline T *UniquePtr<T>::release() noexcept {
    T *tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template <class T>
inline T *UniquePtr<T[]>::release() noexcept {
    T *tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template <class T>
inline void UniquePtr<T>::reset(T *ptr) noexcept {
    delete ptr_;
    ptr_ = ptr;
}

template <class T>
inline void UniquePtr<T[]>::reset(T *ptr) noexcept {
    delete[] ptr_;
    ptr_ = ptr;
}

template <class T>
inline void UniquePtr<T>::swap(UniquePtr<T> &other) noexcept {
    std::swap(ptr_, other.ptr_);
}

template <class T>
inline void UniquePtr<T[]>::swap(UniquePtr<T[]> &other) noexcept {
    std::swap(ptr_, other.ptr_);
}

template <class T>
inline UniquePtr<T>::operator bool() const noexcept {
    return get() != nullptr;
}

template <class T>
inline UniquePtr<T[]>::operator bool() const noexcept {
    return get() != nullptr;
}

template <class T>
inline T *UniquePtr<T>::get() const noexcept {
    return ptr_;
}

template <class T>
inline T *UniquePtr<T[]>::get() const noexcept {
    return ptr_;
}

template <class T>
inline T *UniquePtr<T>::operator->() const noexcept {
    return ptr_;
}

template <class T>
inline T &UniquePtr<T>::operator*() const noexcept {
    return *ptr_;
}

template <class T>
inline T &UniquePtr<T[]>::operator[](std::size_t index) const {
    return ptr_[index];
}
}  // namespace zatsep