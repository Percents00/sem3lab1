#pragma once

#include "Sequence.h"
#include "LinkedList.h"
#include "SharedPtr.h"

template <typename T>
class ListSequence : public Sequence<T> {
private:
    SharedPtr<LinkedList<T>> list;


public:
    ListSequence() : list(new LinkedList<T>()) {}

    ListSequence(const SharedPtr<T>* items, int count) : list(new LinkedList<T>(items, count)) {}

    ListSequence(const ListSequence<T>& other) : list(other.list) {}

    ListSequence<T>& operator=(const ListSequence<T>& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    ~ListSequence() override = default;

    void Append(const SharedPtr<T>& item) override {
        list->Append(item);
    }

    void Prepend(const SharedPtr<T>& item) override {
        list->Prepend(item);
    }


    SharedPtr<Sequence<T>> GetSubSequence(int startIndex, int endIndex) override {
        auto newList = new ListSequence<T>();
        newList->list = SharedPtr<LinkedList<T>>(new LinkedList<T>(list->GetSubList(startIndex, endIndex)));

        return SharedPtr<Sequence<T>>(newList);
    }


    void InsertAt(int index, const SharedPtr<T>& item) override {
        list->InsertAt(index, item);
    }

    SharedPtr<T> GetFirst() const override {
        return list->GetFirst();
    }

    SharedPtr<T> GetLast() const override {
        return list->GetLast();
    }

    SharedPtr<T> Get(int index) const override {
        return list->Get(index);
    }

    int GetLength() const override {
        return list->GetLength();
    }
};