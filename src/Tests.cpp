#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"
using namespace zatsep;

template <typename T>
void bubbleSort(SmartPtrSequence<T>& sequence) {
    size_t length = sequence.get_length();
    for (size_t i = 0; i < length - 1; ++i) {
        for (size_t j = 0; j < length - i - 1; ++j) {
            if (sequence.get(j) > sequence.get(j + 1)) {
                T temp = sequence.get(j);
                sequence.set(j, sequence.get(j + 1));
                sequence.set(j + 1, temp);
            }
        }
    }
}

template <typename T>
void selectionSort(SmartPtrSequence<T>& sequence) {
    size_t length = sequence.get_length();
    for (size_t i = 0; i < length - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < length; ++j) {
            if (sequence.get(j) < sequence.get(minIndex)) {
                minIndex = j;
            }
        }
        T temp = sequence.get(i);
        sequence.set(i, sequence.get(minIndex));
        sequence.set(minIndex, temp);
    }
}

template <typename T>
void insertionSort(SmartPtrSequence<T>& sequence) {
    size_t length = sequence.get_length();
    for (size_t i = 1; i < length; ++i) {
        T key = sequence.get(i);
        int j = i - 1;

        while (j >= 0 && sequence.get(j) > key) {
            sequence.set(j + 1, sequence.get(j));
            --j;
        }

        sequence.set(j + 1, key);
    }
}

template <typename T>
void countingSort(SmartPtrSequence<T>& sequence) {
    T minVal = sequence.get_first();
    T maxVal = sequence.get_first();
    for (size_t i = 1; i < sequence.get_length(); ++i) {
        if (sequence.get(i) < minVal) minVal = sequence.get(i);
        if (sequence.get(i) > maxVal) maxVal = sequence.get(i);
    }

    std::vector<int> countArray(maxVal - minVal + 1, 0);
    for (size_t i = 0; i < sequence.get_length(); ++i) {
        countArray[sequence.get(i) - minVal]++;
    }

    size_t index = 0;
    for (size_t i = 0; i < countArray.size(); ++i) {
        while (countArray[i] > 0) {
            sequence.set(index++, i + minVal);
            countArray[i]--;
        }
    }
}

TEST_CASE("SmartPtrArraySequence functionality") {
    SmartPtrArraySequence<int> sequence;

    SUBCASE("Appending elements") {
        sequence.append(1);
        CHECK(sequence.get_length() == 1);
        CHECK(sequence.get_first() == 1);
        CHECK(sequence.get_last() == 1);

        sequence.append(2);
        CHECK(sequence.get_length() == 2);
        CHECK(sequence.get_first() == 1);
        CHECK(sequence.get_last() == 2);
    }

    SUBCASE("Prepending elements") {
        sequence.prepend(3);
        CHECK(sequence.get_length() == 1);
        CHECK(sequence.get_first() == 3);
        CHECK(sequence.get_last() == 3);

        sequence.prepend(4);
        CHECK(sequence.get_length() == 2);
        CHECK(sequence.get_first() == 4);
        CHECK(sequence.get_last() == 3);
    }

    SUBCASE("Inserting elements") {
        sequence.append(1);
        sequence.append(2);
        sequence.append(3);

        SUBCASE("Insert at the beginning") {
            sequence.insert(0, 5);
            CHECK(sequence.get_length() == 4);
            CHECK(sequence.get(0) == 5);
        }

        SUBCASE("Insert in the middle") {
            sequence.insert(2, 6);
            CHECK(sequence.get_length() == 4);
            CHECK(sequence.get(2) == 6);
        }

        SUBCASE("Insert at the end") {
            sequence.insert(3, 7);
            CHECK(sequence.get_length() == 4);
            CHECK(sequence.get_last() == 7);
        }

        // Trying to insert at an index that is out of range
        CHECK_THROWS(sequence.insert(6, 10));
    }

    SUBCASE("Removing elements") {
        sequence.append(1);
        sequence.append(2);
        sequence.append(3);

        SUBCASE("Remove at valid index") {
            sequence.remove(1);
            CHECK(sequence.get_length() == 2);
            CHECK(sequence.get(1) != 5);
        }

        SUBCASE("Remove at invalid index") {
            CHECK_THROWS(sequence.remove(10));  // Adjust the index to be out of range
        }
    }

    SUBCASE("Getting subsequence") {
        sequence.append(1);
        sequence.append(2);
        sequence.append(3);

        SUBCASE("Valid subsequence") {
            CHECK_NOTHROW({
                auto subsequence = sequence.get_subsequence(0, 1);
                CHECK(subsequence->get_length() == 2);
                CHECK(subsequence->get_first() == sequence.get_first());
                CHECK(subsequence->get_last() == sequence.get(1));
            });
        }

        SUBCASE("Invalid subsequence start index") {
            CHECK_THROWS(sequence.get_subsequence(10, 2));  // Adjust the start index to be out of range
        }
    }

    // Добавьте дополнительные тесты по мере необходимости
}

// Тесты для SmartPtrLinkedListSequence
TEST_CASE("SmartPtrLinkedListSequence functionality") {
    SmartPtrLinkedListSequence<int> sequence;

    SUBCASE("Appending elements") {
        sequence.append(1);
        CHECK(sequence.get_length() == 1);
        CHECK(sequence.get_first() == 1);
        CHECK(sequence.get_last() == 1);

        sequence.append(2);
        CHECK(sequence.get_length() == 2);
        CHECK(sequence.get_first() == 1);
        CHECK(sequence.get_last() == 2);
    }

    SUBCASE("Prepending elements") {
        sequence.prepend(3);
        CHECK(sequence.get_length() == 1);
        CHECK(sequence.get_first() == 3);
        CHECK(sequence.get_last() == 3);

        sequence.prepend(4);
        CHECK(sequence.get_length() == 2);
        CHECK(sequence.get_first() == 4);
        CHECK(sequence.get_last() == 3);
    }

    SUBCASE("Inserting elements") {
        sequence.append(1);
        sequence.append(2);
        sequence.append(3);

        SUBCASE("Insert at valid index") {
            sequence.insert(1, 5);
            CHECK(sequence.get_length() == 4);
            CHECK(sequence.get(1) == 5);
        }

        SUBCASE("Insert at invalid index") {
            CHECK_THROWS(sequence.insert(10, 6));  // Adjust the index to be out of range
        }
    }

    SUBCASE("Removing elements") {
        sequence.append(1);
        sequence.append(2);
        sequence.append(3);

        SUBCASE("Remove at valid index") {
            sequence.remove(1);
            CHECK(sequence.get_length() == 2);
            CHECK(sequence.get(1) != 5);
        }

        SUBCASE("Remove at invalid index") {
            CHECK_THROWS(sequence.remove(10));  // Adjust the index to be out of range
        }
    }
    SUBCASE("Getting subsequence") {
        sequence.append(1);
        sequence.append(2);
        sequence.append(3);

        SUBCASE("Valid subsequence") {
            CHECK_NOTHROW({
                auto subsequence = sequence.get_subsequence(0, 1);
                CHECK(subsequence->get_length() == 2);
                CHECK(subsequence->get_first() == sequence.get_first());
                CHECK(subsequence->get_last() == sequence.get(1));
            });
        }

        SUBCASE("Invalid subsequence start index") {
            CHECK_THROWS(sequence.get_subsequence(10, 2));  // Adjust the start index to be out of range
        }
    }

    // Добавьте дополнительные тесты по мере необходимости
}

// Тесты для сортировок
TEST_CASE("Sorting algorithms") {
    SmartPtrArraySequence<int> arraySequence;
    arraySequence.append(5);
    arraySequence.append(3);
    arraySequence.append(8);

    SmartPtrLinkedListSequence<int> linkedListSequence;
    linkedListSequence.append(5);
    linkedListSequence.append(3);
    linkedListSequence.append(8);

    SUBCASE("Bubble Sort for Array Sequence") {
        bubbleSort(arraySequence);
        CHECK(arraySequence.get(0) == 3);
        CHECK(arraySequence.get(1) == 5);
        CHECK(arraySequence.get(2) == 8);
    }

    SUBCASE("Selection Sort for Array Sequence") {
        selectionSort(arraySequence);
        CHECK(arraySequence.get(0) == 3);
        CHECK(arraySequence.get(1) == 5);
        CHECK(arraySequence.get(2) == 8);
    }

    SUBCASE("Insertion Sort for Array Sequence") {
        insertionSort(arraySequence);
        CHECK(arraySequence.get(0) == 3);
        CHECK(arraySequence.get(1) == 5);
        CHECK(arraySequence.get(2) == 8);
    }

    SUBCASE("Counting Sort for Array Sequence") {
        countingSort(arraySequence);
        CHECK(arraySequence.get(0) == 3);
        CHECK(arraySequence.get(1) == 5);
        CHECK(arraySequence.get(2) == 8);
    }

    SUBCASE("Bubble Sort for LinkedList Sequence") {
        bubbleSort(linkedListSequence);
        CHECK(linkedListSequence.get(0) == 3);
        CHECK(linkedListSequence.get(1) == 5);
        CHECK(linkedListSequence.get(2) == 8);
    }

    SUBCASE("Selection Sort for LinkedList Sequence") {
        selectionSort(linkedListSequence);
        CHECK(linkedListSequence.get(0) == 3);
        CHECK(linkedListSequence.get(1) == 5);
        CHECK(linkedListSequence.get(2) == 8);
    }

    SUBCASE("Insertion Sort for LinkedList Sequence") {
        insertionSort(linkedListSequence);
        CHECK(linkedListSequence.get(0) == 3);
        CHECK(linkedListSequence.get(1) == 5);
        CHECK(linkedListSequence.get(2) == 8);
    }

    SUBCASE("Counting Sort for LinkedList Sequence") {
        countingSort(linkedListSequence);
        CHECK(linkedListSequence.get(0) == 3);
        CHECK(linkedListSequence.get(1) == 5);
        CHECK(linkedListSequence.get(2) == 8);
    }

    // Добавьте дополнительные тесты
}