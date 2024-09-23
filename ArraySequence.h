#pragma once
#include <stdexcept>

template <typename T>
class ArraySequence : public Sequence<T> {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    ArraySequence() : data(nullptr), size(0), capacity(0) {}

    ~ArraySequence() {
        delete[] data;
    }

    void push_back(const T& value) override {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    void pop_back() override {
        if (size > 0) {
            --size;
        }
    }

    T& operator[](size_t index) override {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const override {
        return size;
    }
};
