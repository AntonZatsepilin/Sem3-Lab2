#include "ControlBlock.hpp"
namespace zatsep {
template <class T>
inline ControlBlock<T>::ControlBlock(T *ptr) {  // constructor from pointer
    if (!ptr) throw std::exception();
    ptr_ = ptr;
    reference_counter_ = 1;
    weak_ptr_reference_counter_ = 0;
}

template <class T>
inline ControlBlock<T[]>::ControlBlock(T *ptr) {  // constructor from pointer for arrays
    if (!ptr) throw std::invalid_argument("ptr is nullptr");

    ptr_ = ptr;
    reference_counter_ = 1;
    weak_ptr_reference_counter_ = 0;
}

template <class T>
inline void ControlBlock<T>::increment_reference_counter() noexcept {
    ++reference_counter_;
}

template <class T>
inline void ControlBlock<T[]>::increment_reference_counter() noexcept {
    ++reference_counter_;
}

template <class T>
inline void ControlBlock<T>::decrement_reference_counter_and_delete_if_zero() {
    if (reference_counter_ == 0) throw std::invalid_argument("reference_counter_ is 0");

    if (reference_counter_ == 1 && ptr_ != nullptr) {
        delete ptr_;
        ptr_ = nullptr;
    }
    --reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline void ControlBlock<T[]>::decrement_reference_counter_and_delete_if_zero() {
    if (reference_counter_ == 0) throw std::invalid_argument("reference_counter_ is 0");

    if (reference_counter_ == 1 && ptr_ != nullptr) {
        delete[] ptr_;
        ptr_ = nullptr;
    }
    --reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline void ControlBlock<T>::increment_weak_ptr_reference_counter() noexcept {
    ++weak_ptr_reference_counter_;
}

template <class T>
inline void ControlBlock<T[]>::increment_weak_ptr_reference_counter() noexcept {
    ++weak_ptr_reference_counter_;
}

template <class T>
inline void ControlBlock<T>::decrement_weak_ptr_reference_counter_and_delete_if_zero() {
    if (weak_ptr_reference_counter_ == 0) throw std::invalid_argument("weak_ptr_reference_counter_ is 0");

    --weak_ptr_reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline void ControlBlock<T[]>::decrement_weak_ptr_reference_counter_and_delete_if_zero() {
    if (weak_ptr_reference_counter_ == 0) throw std::invalid_argument("weak_ptr_reference_counter_ is 0");

    --weak_ptr_reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline T *ControlBlock<T>::get() const noexcept {
    return ptr_;
}

template <class T>
inline T *ControlBlock<T[]>::get() const noexcept {
    return ptr_;
}

template <class T>
inline unsigned int ControlBlock<T>::get_reference_counter() const noexcept {
    return reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T[]>::get_reference_counter() const noexcept {
    return reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T>::get_weak_ptr_reference_counter() const noexcept {
    return weak_ptr_reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T[]>::get_weak_ptr_reference_counter() const noexcept {
    return weak_ptr_reference_counter_;
}
}  // namespace zatsep