#ifndef LAB1_my_shared_ptr_H
#define LAB1_my_shared_ptr_H

#include <cstddef>
#include <utility>

template <typename T>
class ControlBlock {
   public:
    explicit ControlBlock(size_t c);
    size_t count = 0;
};

template <typename T>
class my_shared_ptr {
   public:
    my_shared_ptr();
    explicit my_shared_ptr(T* ptr_);
    my_shared_ptr(const my_shared_ptr<T>& other);
    my_shared_ptr(my_shared_ptr<T>&& other) noexcept;
    ~my_shared_ptr();
    T* get();

    template <typename U, typename... Args>
    friend my_shared_ptr<U> make_shared_personal(Args... args);

   private:
    T* ptr;
    ControlBlock<T>* block;
};

template <typename U, typename... Args>
my_shared_ptr<U> make_shared_personal(Args... args);

#include "SharedPtr.tpp"

#endif
