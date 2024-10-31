#include <iostream>
#include <vector>
#include <limits>

#include "LinkedList.h"
#include "ListSequence.h"
#include "SharedPtr.h"
#include "UniquePtr.h"


void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
void demonstrateListSequence() {
    ListSequence<T> listSeq;
    int choice;

    do {
        std::cout << "\nList Sequence Operations:\n";
        std::cout << "1. Append\n";
        std::cout << "2. Prepend\n";
        std::cout << "3. Insert at\n";
        std::cout << "4. Get\n";
        std::cout << "5. Get First\n";
        std::cout << "6. Get Last\n";
        std::cout << "7. Get Subsequence\n";
        std::cout << "8. Get Length\n";
        std::cout << "9. Print\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clearInputBuffer();
        system("cls");


        switch (choice) {
            case 1: {
                T value;
                std::cout << "Enter value to append: ";
                std::cin >> value;
                listSeq.Append(SharedPtr<T>(new T(value)));
                break;
            }
            case 2: {
                T value;
                std::cout << "Enter value to prepend: ";
                std::cin >> value;
                listSeq.Prepend(SharedPtr<T>(new T(value)));
                break;
            }
            case 3: {
                int index;
                T value;
                std::cout << "Enter index to insert at: ";
                std::cin >> index;
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                try {
                    listSeq.InsertAt(index, SharedPtr<T>(new T(value)));
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 4: {
                int index;
                std::cout << "Enter index to get: ";
                std::cin >> index;
                try {
                    SharedPtr<T> element = listSeq.Get(index);
                    std::cout << "Element at index " << index << ": " << *element << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 5: {
                try {
                    SharedPtr<T> first = listSeq.GetFirst();
                    std::cout << "First element: " << *first << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

                break;
            }
            case 6: {
                try {
                    SharedPtr<T> last = listSeq.GetLast();
                    std::cout << "Last element: " << *last << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 7: {
                int startIndex, endIndex;
                std::cout << "Enter start index for subsequence: ";
                std::cin >> startIndex;
                std::cout << "Enter end index for subsequence: ";
                std::cin >> endIndex;
                try {
                    auto subSeq = listSeq.GetSubSequence(startIndex, endIndex);
                    std::cout << "Subsequence: [";
                    for(int i = 0; i < subSeq->GetLength(); ++i){
                        if(i > 0) std::cout << ", ";

                        std::cout << *subSeq->Get(i);
                    }

                    std::cout << "]\n";
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 8: {
                std::cout << "Length: " << listSeq.GetLength() << std::endl;
                break;
            }
            case 9: {
                std::cout << "List Sequence: [";
                for (int i = 0; i < listSeq.GetLength(); ++i) {
                    if (i > 0) std::cout << ", ";
                    std::cout << *listSeq.Get(i);
                }
                std::cout << "]\n";
                break;
            }
            case 0:
                std::cout << "Exiting ListSequence demonstration.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}



int runGUI() {
    int dataTypeChoice;

    do {
        std::cout << "\nChoose data type:\n";
        std::cout << "1. int\n";
        std::cout << "2. double\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> dataTypeChoice;
        clearInputBuffer();


        switch (dataTypeChoice) {
            case 1:
                demonstrateListSequence<int>();
                break;
            case 2:
                demonstrateListSequence<double>();
                break;
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (dataTypeChoice != 0);

    return 0;
}