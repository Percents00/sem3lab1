#include <iostream>
#include <cassert>

#include "SmartPointers.h"

void testCreationAndDestruction() {
    {
        SmartPtr<int> sp(new int(42));
        assert(*sp == 42);
        assert(sp.getRefCount() == 1);
    }

    std::cout << "Test 1 passed: creation and destruction" << std::endl;
}

void testCopyingSmartPointer() {
    {
        SmartPtr<int> sp1(new int(42));
        SmartPtr<int> sp2 = sp1;
        assert(sp1.getRefCount() == 2);
        assert(sp2.getRefCount() == 2);
        assert(*sp1 == 42);
        assert(*sp2 == 42);
    }
    std::cout << "Test 2 passed: Copying smart pointer\n";
}

class Base {
public:
    virtual int getValue() const { return 10; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    int getValue() const override { return 20; }
};

void testPointerToClasses() {
    {
        SmartPtr<Base> basePtr(new Base());
        assert(basePtr->getValue() == 10);

        SmartPtr<Base> derivedPtr(new Derived());
        assert(derivedPtr->getValue() == 20);
        assert(derivedPtr.getRefCount() == 1);
    }
    std::cout << "Test 5 passed: Pointer to classes (inheritance)\n";
}

int main() {
    testCreationAndDestruction();
    testCopyingSmartPointer();;
    testPointerToClasses();
    std::cout << "All tests passed successfully!\n";
    return 0;
}