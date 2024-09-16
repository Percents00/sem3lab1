#pragma once

template <typename T>
class SmartPtr {
private:
    T* ptr;
    size_t* refCount;
public:
    SmartPtr(T* p = nullptr) : ptr(p) {
        refCount = new size_t(1);
    }

    SmartPtr(const SmartPtr<T>& other) {
        ptr = other.ptr;
        refCount = other.refCount;
        ++(*refCount);
    }


    SmartPtr<T>& operator=(const SmartPtr<T>& other) {
        if (this != &other) {
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount);
        }
        return *this;
    }

    ~SmartPtr() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }


    size_t getRefCount() { return *refCount; }
};