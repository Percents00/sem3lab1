#pragma once

template <typename T>
class SmartPtr {
private:
    T* ptr;
    size_t* refCount;

public:

    SmartPtr() : ptr(nullptr), refCount(nullptr) {}

    SmartPtr(T* p = nullptr) : ptr(p) {
        refCount = (p != nullptr) ? new size_t(1) : nullptr;
    }

    SmartPtr(const SmartPtr<T>& other) : ptr(other.ptr), refCount(other.refCount) {
        if (ptr != nullptr) {
            ++(*refCount);
        }
    }


    SmartPtr<T>& operator=(const SmartPtr<T>& other) {
        if (this != &other) {
            if (--(*refCount) == 0) {
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
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    T& operator*() {
        if (ptr == nullptr) {
            throw std::runtime_error("null SmartPtr");
        }
        return *ptr;
    }


    T* operator->() {
        if (ptr == nullptr) {
            throw std::runtime_error("null SmartPtr");
        }
    }


    size_t getRefCount() { return (refCount != nullptr) ? *refCount : 0; }
};
