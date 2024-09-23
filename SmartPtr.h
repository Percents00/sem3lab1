#pragma once

#include <stdexcept>
#include <cstddef>

template <typename T>
class SmartPtr {
private:
    T* ptr;
    size_t* refCount;

public:
    SmartPtr() : ptr(nullptr), refCount(nullptr) {}

    explicit SmartPtr(T* p) : ptr(p) {
        refCount = (p != nullptr) ? new size_t(1) : nullptr;
    }

    SmartPtr(const SmartPtr<T>& other) : ptr(other.ptr), refCount(other.refCount) {
        if (ptr != nullptr) {
            ++(*refCount);
        }
    }

    SmartPtr<T>& operator=(const SmartPtr<T>& other) {
        if (this != &other) {
            if (refCount != nullptr && --(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }

            ptr = other.ptr;
            refCount = other.refCount;

            if (ptr != nullptr) {
                ++(*refCount);
            }
        }
        return *this;
    }

    ~SmartPtr() {
        if (refCount != nullptr && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    T& operator*() const {
        if (ptr == nullptr) {
            throw std::runtime_error("null SmartPtr dereference");
        }
        return *ptr;
    }

    T* operator->() const {
        if (ptr == nullptr) {
            throw std::runtime_error("null SmartPtr dereference");
        }
        return ptr;
    }

    size_t getRefCount() const {
        return (refCount != nullptr) ? *refCount : 0;
    }

    bool isNull() const {
        return ptr == nullptr;
    }
};
