#ifndef LAB1_my_unique_ptr_H
#define LAB1_my_unique_ptr_H

#include <utility>

template <typename T>
class my_unique_ptr {
   public:
    my_unique_ptr() = default;

    explicit my_unique_ptr(T* ptr);

    my_unique_ptr(my_unique_ptr<T>&& other) noexcept;

    my_unique_ptr<T>& operator=(const my_unique_ptr<T>& other) = delete;

    my_unique_ptr(const my_unique_ptr<T>& other) = default;

    ~my_unique_ptr();

    T* release();

    void reset(T* new_ptr);

    T* get();

    template <typename U, typename... Args>
    friend my_unique_ptr<U> make_my_unique_personal(Args... args);

   private:
    T* ptr = nullptr;
};

template <typename U, typename... Args>
my_unique_ptr<U> make_my_unique_personal(Args... args);

#include "UniquePtr.tpp"

#endif
