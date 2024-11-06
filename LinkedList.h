#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include "SharedPtr.h"

template<class T>
class Node {
public:
    T data;
    SharedPtr<Node<T>> next;

    Node(const T& data) : data(data), next(nullptr) {}
};

template<class T>
class LinkedList {
private:
    SharedPtr<Node<T>> head;
    SharedPtr<Node<T>> tail;
    int size;


public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(const T *items, int count) : head(nullptr), tail(nullptr), size(0) {
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &list) : head(nullptr), size(0) {
        *this = list;
    }

    ~LinkedList() = default;

    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
        SharedPtr<Node<T>> current = other.head;
        while (!current.isNull()) {
            Append(current->data);
            current = current->next;
        }
    }

    SharedPtr<T> GetFirst() const {
        if (head.isNull()) {
            throw std::out_of_range("ListIsEmpty");
        }
         return SharedPtr<T>(new T(head->data));
    }

    SharedPtr<T> GetLast() const {
        if (head.isNull()) {
            throw std::out_of_range("ListIsEmpty");
        }
        SharedPtr<Node<T>> temp = head;
        while (!temp->next.isNull()) {
            temp = temp->next;
        }
        return SharedPtr<T>(new T(temp->data));
    }

    SharedPtr<T> Get(int index) const {
        checkIndex(index);
        SharedPtr<Node<T>> temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return SharedPtr<T>(new T(temp->data));
    }

    LinkedList<T> GetSubList(int startIndex, int endIndex) const {
        checkIndex(startIndex);
        checkIndex(endIndex);
        LinkedList<T> sublist;
        SharedPtr<Node<T>> current = head;
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
        SharedPtr<Node<T>> newNode(new Node<T>(item));
        if (head.isNull()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void Prepend(const SharedPtr<T>& item) {
        SharedPtr<Node<T>> newNode(new Node<T>(item));
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

        SharedPtr<Node<T>> prev = head;
        for (int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }

        SharedPtr<Node<T>> newNode(new Node<T>(item));
        newNode->next = prev->next;
        prev->next = newNode;

        size++;
    }



    
    LinkedList<T>& operator=(const LinkedList<T>& other) {
      if(this != &other){
        head = nullptr;
        tail = nullptr;
        size = 0;
        SharedPtr<Node<T>> current = other.head;
        while(!current.isNull()){
          Append(current->data);
          current = current->next;
        }

      }
      return *this;

    }


private:
    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("IndexOutOfRange");
        }
    }
};

#endif
