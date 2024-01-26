#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"

using namespace zatsep;
using namespace std::chrono;

template <typename T>
void bubbleSort(SmartPtrSequence<T>& sequence) {
    auto start = high_resolution_clock::now();
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
    auto stop = high_resolution_clock::now();  // Замер времени завершения сортировки
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "Время выполнения сортировки: " << duration.count() << " мс.\n";
}

template <typename T>
void selectionSort(SmartPtrSequence<T>& sequence) {
    auto start = high_resolution_clock::now();
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
    auto stop = high_resolution_clock::now();  // Замер времени завершения сортировки
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "Время выполнения сортировки: " << duration.count() << " мс.\n";
}

template <typename T>
void insertionSort(SmartPtrSequence<T>& sequence) {
    auto start = high_resolution_clock::now();
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
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "Время выполнения сортировки: " << duration.count() << " мс.\n";
}

template <typename T>
void countingSort(SmartPtrSequence<T>& sequence) {
    auto start = high_resolution_clock::now();

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "Время выполнения сортировки подсчетом: " << duration.count() << " мс.\n";
}

int generateRandomNumber(int min, int max) { return rand() % (max - min + 1) + min; }

void printMenu() {
    std::cout << "\n========================================\n";
    std::cout << "              Ваше меню\n";
    std::cout << "========================================\n";
    std::cout << std::setw(2) << "1. "
              << "Создать SmartPtrArraySequence\n";
    std::cout << std::setw(2) << "2. "
              << "Создать SmartPtrLinkedListSequence\n";
    std::cout << std::setw(2) << "3. "
              << "Заполнить последовательность случайными числами\n";
    std::cout << std::setw(2) << "4. "
              << "Вывести последовательность\n";
    std::cout << std::setw(2) << "5. "
              << "Вставить элемент\n";
    std::cout << std::setw(2) << "6. "
              << "Удалить элемент\n";
    std::cout << std::setw(2) << "7. "
              << "Получить подпоследовательность\n";
    std::cout << std::setw(2) << "8. "
              << "Объединить с другой последовательностью\n";
    std::cout << std::setw(2) << "9. "
              << "Очистить последовательность\n";
    std::cout << std::setw(2) << "10. "
              << "Сортировка методом пузырька\n";
    std::cout << std::setw(2) << "11. "
              << "Сортировка методом простого выбора\n";
    std::cout << std::setw(2) << "12. "
              << "Сортировка методом простых вставок\n";
    std::cout << std::setw(2) << "13. "
              << "Сортировка методом подсчёта\n";
    std::cout << std::setw(2) << "0. "
              << "Выйти\n";
    std::cout << "========================================\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    SmartPtrSequence<int>* sequence = nullptr;

    while (true) {
        printMenu();

        int choice;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                sequence = new SmartPtrArraySequence<int>();
                std::cout << "SmartPtrArraySequence создан.\n";
                break;
            }
            case 2: {
                sequence = new SmartPtrLinkedListSequence<int>();
                std::cout << "SmartPtrLinkedListSequence создан.\n";
                break;
            }
            case 3: {
                if (sequence) {
                    int length;
                    std::cout << "Введите длину последовательности: ";
                    std::cin >> length;

                    for (int i = 0; i < length; ++i) {
                        sequence->append(generateRandomNumber(-1000000, 1000000));
                    }

                    std::cout << "Последовательность заполнена случайными числами.\n";
                } else {
                    std::cout << "Сначала создайте последовательность.\n";
                }
                break;
            }
            case 4: {
                if (sequence) {
                    std::cout << "Последовательность: " << sequence->to_string() << "\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 5: {
                if (sequence) {
                    int index, value;
                    std::cout << "Введите индекс для вставки: ";
                    std::cin >> index;
                    std::cout << "Введите значение: ";
                    std::cin >> value;

                    sequence->insert(index, value);
                    std::cout << "Элемент вставлен.\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 6: {
                if (sequence) {
                    int index;
                    std::cout << "Введите индекс для удаления: ";
                    std::cin >> index;

                    sequence->remove(index);
                    std::cout << "Элемент удален.\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 7: {
                if (sequence) {
                    int start, end;
                    std::cout << "Введите начальный индекс: ";
                    std::cin >> start;
                    std::cout << "Введите конечный индекс: ";
                    std::cin >> end;

                    auto subsequence = sequence->get_subsequence(start, end);
                    std::cout << "Подпоследовательность: " << subsequence->to_string() << "\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 8: {
                if (sequence) {
                    int length;
                    std::cout << "Введите длину второй последовательности: ";
                    std::cin >> length;

                    SmartPtrSequence<int>* secondSequence = new SmartPtrArraySequence<int>();
                    for (int i = 0; i < length; ++i) {
                        secondSequence->append(generateRandomNumber(-1000000, 1000000));
                    }

                    auto result = sequence->concat(SharedPtr<SmartPtrSequence<int>>(secondSequence));
                    std::cout << "Результат объединения: " << result->to_string() << "\n";
                } else {
                    std::cout << "Сначала создайте или заполните первую последовательность.\n";
                }
                break;
            }
            case 9: {
                if (sequence) {
                    sequence->clear();
                    std::cout << "Последовательность очищена.\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 10: {
                if (sequence) {
                    bubbleSort(*sequence);
                    std::cout << "Последовательность отсортирована методом пузырька.\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 11: {
                if (sequence) {
                    selectionSort(*sequence);
                    std::cout << "Последовательность отсортирована методом простого выбора.\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 12: {
                if (sequence) {
                    insertionSort(*sequence);
                    std::cout << "Последовательность отсортирована методом простых вставок.\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 13: {
                if (sequence) {
                    countingSort(*sequence);
                    std::cout << "Последовательность отсортирована методом подсчета.\n";
                } else {
                    std::cout << "Сначала создайте или заполните последовательность.\n";
                }
                break;
            }
            case 0: {
                if (sequence) {
                    delete sequence;
                }
                std::cout << "Программа завершена.\n";
                return 0;
            }
            default:
                std::cout << "Некорректный ввод. Пожалуйста, выберите правильное действие.\n";
        }
    }

    return 0;
}
