#pragma once

#include <stdexcept>

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T* p) : ptr(p) {}

    ~UniquePtr() {
        delete ptr;
    }

    UniquePtr(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() {
        if (!ptr) {
            throw std::runtime_error("Dereferencing null UniquePtr");
        }
        return *ptr;
    }

    const T& operator*() const {
        if (!ptr) {
            throw std::runtime_error("Dereferencing null UniquePtr");
        }
        return *ptr;
    }

    T* operator->() {
        if (!ptr) {
            return nullptr;
        }
        return ptr;
    }

    const T* operator->() const {
        if (!ptr) {
            return nullptr;
        }
        return ptr;
    }

    T* get() const {
        return ptr;
    }

    // T* release() {
    //     T* temp = ptr;
    //     ptr = nullptr;
    //     return temp;
    // }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    bool isNull() const {
        return ptr == nullptr;
    }
};
