#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "SmartPointers/SharedPtr/SharedPtr.hpp"
#include "SmartPointers/UniquePtr/UniquePtr.hpp"
#include "doctest.h"

TEST_CASE("my_unique_ptr tests") {
    SUBCASE("Creating my_unique_ptr") {
        auto ptr = make_my_unique_personal<int>(42);
        CHECK(*ptr.get() == 42);
    }

    SUBCASE("Creating my_unique_ptr with char") {
        auto ptr = make_my_unique_personal<char>('X');
        CHECK(*ptr.get() == 'X');
    }

    SUBCASE("Creating my_unique_ptr with string") {
        auto ptr = make_my_unique_personal<std::string>("doctest");
        CHECK(*ptr.get() == "doctest");
    }

    SUBCASE("my_unique_ptr move constructor") {
        auto ptr1 = make_my_unique_personal<int>(42);
        auto ptr2 = std::move(ptr1);
        CHECK(ptr1.get() == nullptr);
        CHECK(*ptr2.get() == 42);
    }

    SUBCASE("my_unique_ptr release") {
        auto ptr = make_my_unique_personal<int>(42);
        int* released = ptr.release();
        CHECK(ptr.get() == nullptr);
        CHECK(*released == 42);
        delete released;
    }

    SUBCASE("my_unique_ptr reset") {
        auto ptr = make_my_unique_personal<int>(42);
        ptr.reset(new int(24));
        CHECK(*ptr.get() == 24);
    }

    SUBCASE("my_unique_ptr reset with nullptr") {
        auto ptr = make_my_unique_personal<int>(42);
        ptr.reset(nullptr);
        CHECK(ptr.get() == nullptr);
    }

    SUBCASE("my_unique_ptr get") {
        auto ptr = make_my_unique_personal<int>(42);
        CHECK(ptr.get() != nullptr);
        CHECK(*ptr.get() == 42);
    }

    SUBCASE("my_unique_ptr destructor") {
        int* destructorCheck = new int;
        {
            auto ptr = make_my_unique_personal<int>(42);
            destructorCheck = ptr.get();
        }
    }

    SUBCASE("my_unique_ptr custom type") {
        struct CustomType {
            int value;
            CustomType(int val) : value(val) {}
        };

        auto ptr = make_my_unique_personal<CustomType>(42);
        CHECK(ptr.get() != nullptr);
        CHECK(ptr.get()->value == 42);
    }
}

TEST_CASE("my_shared_ptr tests") {
    SUBCASE("Creating my_shared_ptr") {
        auto ptr = make_shared_personal<int>(42);
        CHECK(*ptr.get() == 42);
    }

    SUBCASE("Creating my_shared_ptr with char") {
        auto ptr = make_shared_personal<char>('X');
        CHECK(*ptr.get() == 'X');
    }

    SUBCASE("Creating my_shared_ptr with string") {
        auto ptr = make_shared_personal<std::string>("doctest");
        CHECK(*ptr.get() == "doctest");
    }

    SUBCASE("my_shared_ptr copy constructor") {
        auto ptr1 = make_shared_personal<int>(42);
        auto ptr2 = ptr1;
        CHECK(*ptr1.get() == 42);
        CHECK(*ptr2.get() == 42);
        CHECK(ptr1.get() == ptr2.get());  // Should point to the same object, but different ControlBlocks
    }

    SUBCASE("my_shared_ptr move constructor") {
        auto ptr1 = make_shared_personal<int>(42);
        auto ptr2 = std::move(ptr1);
        CHECK(*ptr2.get() == 42);
        CHECK(ptr1.get() == nullptr);
    }

    SUBCASE("my_shared_ptr get") {
        auto ptr = make_shared_personal<int>(42);
        CHECK(ptr.get() != nullptr);
        CHECK(*ptr.get() == 42);
    }

    SUBCASE("my_shared_ptr destructor") {
        int* destructorCheck = new int;
        {
            auto ptr = make_shared_personal<int>(42);
            destructorCheck = ptr.get();
        }
    }

    SUBCASE("my_shared_ptr custom type") {
        struct CustomType {
            int value;
            CustomType(int val) : value(val) {}
        };

        auto ptr = make_shared_personal<CustomType>(42);
        CHECK(ptr.get() != nullptr);
        CHECK(ptr.get()->value == 42);
    }
}