#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include "SharedPtr.h"

template<class T>
class Node {
public:
    SharedPtr<T> data;
    Node<T> *next;

    Node(const SharedPtr<T>& value) : data{value}, next{nullptr} {}
};

template<class T>
class LinkedList {
private:
    Node<T> *head;
    int size;


    void destroyList() {
        Node<T> *temp = head;
        while (temp) {
            Node<T> *next = temp->next;
            delete temp; // SharedPtr handles the data deletion
            temp = next;
        }
        head = nullptr;
        size = 0;
    }

    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
    }

public:
    LinkedList() : head{nullptr}, size{0} {}

    LinkedList(const SharedPtr<T> *items, int count) : head{nullptr}, size{0} {
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }




    LinkedList(const LinkedList<T> &list) : head{nullptr}, size{0} {
        *this = list;
    }

    ~LinkedList() {
        destroyList();
    }



    SharedPtr<T>& GetFirst() const {
        if (!head) {
            throw std::out_of_range("ListIsEmpty");
        }
        return head->data;
    }

    SharedPtr<T>& GetLast() const {
        if (!head) {
            throw std::out_of_range("ListIsEmpty");
        }
        Node<T> *temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp->data;
    }

    SharedPtr<T>& Get(int index) const {
        checkIndex(index);
        Node<T> *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    LinkedList<T> GetSubList(int startIndex, int endIndex) const {
        checkIndex(startIndex);
        checkIndex(endIndex);
        LinkedList<T> sublist;
        Node<T>* current = head;
        for (int i = 0; i < startIndex; ++i) {
            current = current->next;
        }

        for (int i = startIndex; i <= endIndex; ++i) {
            sublist.Append(current->data);
            current = current->next;
        }
        return sublist;
    }


    int GetLength() const {
        return size;
    }

    void Append(const SharedPtr<T>& item) {
        Node<T>* newNode = new Node<T>(item);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    void Prepend(const SharedPtr<T>& item) {
        Node<T> *newNode = new Node<T>(item);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void InsertAt(int index, const SharedPtr<T>& item) {

        if (index == 0) {
            Prepend(item);
            return;
        }

        checkIndex(index);


        Node<T>* prev = head;
        for(int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }

        Node<T>* newNode = new Node<T>(item);
        newNode->next = prev->next;
        prev->next = newNode;


        size++;
    }

    LinkedList<T> *Concatenate(const LinkedList<T> &other) const {
        auto newList = new LinkedList<T>;
        Node<T> *temp = head;
        while (temp) {
            newList->Append(temp->data);
            temp = temp->next;
        }
        temp = other.head;
        while (temp) {
            newList->Append(temp->data);
            temp = temp->next;
        }
        return newList;
    }
};

#endif