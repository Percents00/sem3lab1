#pragma once

#include "SharedPtr.h"

template <typename T>
class WeakPtr {
private:
    T* ptr;
    size_t* refCount;

public:
    WeakPtr() : ptr(nullptr), refCount(nullptr) {}

    WeakPtr(const SharedPtr<T>& other) : ptr(other.get()), refCount(other.refCount ? other.refCount : nullptr) {}

    WeakPtr(const WeakPtr<T>& other) : ptr(other.ptr), refCount(other.refCount) {}

    WeakPtr& operator=(const WeakPtr<T>& other) {
        ptr = other.ptr;
        refCount = other.refCount;
        return *this;
    }

    WeakPtr(WeakPtr&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
      if (this != &other) {
        ptr = other.ptr;
        refCount = other.refCount;

        other.ptr = nullptr;
        other.refCount = nullptr;
      }
      return *this;
    }



    ~WeakPtr() = default;

    SharedPtr<T> lock() const {
        if (refCount && *refCount > 0) {
            return SharedPtr<T>(ptr, refCount);
        } else {
            return SharedPtr<T>();
        }
    }


    bool expired() const {
        return !refCount || *refCount == 0;
    }
};