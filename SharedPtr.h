#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* refCount;


    void release() {
        if (refCount && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

public:
    SharedPtr() : ptr(nullptr), refCount(nullptr) {}

    explicit SharedPtr(T* p) : ptr(p), refCount(new size_t(1)) {}

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            (*refCount)++;
        }
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();

            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                (*refCount)++;
            }
        }

        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();

            ptr = other.ptr;
            refCount = other.refCount;

            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    ~SharedPtr() {
        release();
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

    size_t use_count() const {
        return refCount ? *refCount : 0;
    }

    bool isNull() const {
         return ptr == nullptr;
    }
};
