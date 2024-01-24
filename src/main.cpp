#include <cstdlib>
#include <ctime>
#include <iostream>

#include "smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"

int main() {
    char choice;
    int length;

    // Choose the sequence type
    std::cout << "Choose sequence type (A: Array, L: Linked List): ";
    std::cin >> choice;

    SmartPtrSequence<int>* sequence;

    if (choice == 'A' || choice == 'a') {
        std::cout << "Enter the length of the array sequence: ";
        std::cin >> length;
        sequence = new SmartPtrArraySequence<int>();
    } else if (choice == 'L' || choice == 'l') {
        std::cout << "Enter the length of the linked list sequence: ";
        std::cin >> length;
        sequence = new SmartPtrLinkedListSequence<int>();
    } else {
        std::cerr << "Invalid choice. Exiting..." << std::endl;
        return 1;
    }

    int value, index;
    UniquePtr<SmartPtrSequence<int>> subsequence;

    while (true) {
        // Display menu
        std::cout << "\nMenu:\n";
        std::cout << "1. Print sequence\n";
        std::cout << "2. Append\n";
        std::cout << "3. Prepend\n";
        std::cout << "4. Insert\n";
        std::cout << "5. Remove\n";
        std::cout << "6. Get subsequence\n";
        std::cout << "7. Clear\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << sequence->to_string() << std::endl;
                break;
            case '2':
                std::cout << "Enter value to append: ";
                std::cin >> value;
                sequence->append(value);
                break;
            case '3':
                std::cout << "Enter value to prepend: ";
                std::cin >> value;
                sequence->prepend(value);
                break;
            case '4':
                std::cout << "Enter index to insert: ";
                std::cin >> index;
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                sequence->insert(index, value);
                break;
            case '5':
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                sequence->remove(index);
                break;
            case '6':
                int start, end;
                std::cout << "Enter start index: ";
                std::cin >> start;
                std::cout << "Enter end index: ";
                std::cin >> end;
                subsequence = UniquePtr<SmartPtrSequence<int>>(sequence->get_subsequence(start, end).release());
                std::cout << "Subsequence: " << subsequence->to_string() << std::endl;
                break;
            case '7':
                sequence->clear();
                std::cout << "Sequence cleared.\n";
                break;
            case '0':
                delete sequence;
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cerr << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
