#include "SharedPtr.h"
#include "SmartPtr.h"
#include "UniquePtr.h"
#include ""
#include <cassert>
#include <iostream>

class TestClass {
public:
    int value;

    TestClass(int val = 0) : value(val) {
        std::cout << "TestClass constructor: " << value << std::endl;
    }

    ~TestClass() {
        std::cout << "TestClass destructor: " << value << std::endl;
    }
};

void TestSharedPtr() {
    std::cout << "----- SharedPtr Tests -----" << std::endl;

    SharedPtr<TestClass> ptr1;
    assert(ptr1.isNull());
    assert(ptr1.use_count() == 0);

    SharedPtr<TestClass> ptr2(new TestClass(10));
    assert(!ptr2.isNull());
    assert(ptr2.use_count() == 1);
    assert(ptr2->value == 10);

    SharedPtr<TestClass> ptr3(ptr2);
    assert(ptr2.use_count() == 2);
    assert(ptr3.use_count() == 2);
    assert(ptr2.get() == ptr3.get());

    SharedPtr<TestClass> ptr4;
    ptr4 = ptr3;
    assert(ptr3.use_count() == 3);
    assert(ptr4.use_count() == 3);
    assert(ptr3.get() == ptr4.get());

    SharedPtr<TestClass> ptr5(std::move(ptr4)); 
    assert(ptr4.isNull()); 
    assert(ptr4.use_count() == 0); 
    assert(ptr5.use_count() == 3); 

    SharedPtr<TestClass> ptr6;
    ptr6 = std::move(ptr5);
    assert(ptr5.isNull()); 
    assert(ptr5.use_count() == 0); 
    assert(ptr6.use_count() == 3); 


    std::cout << "----- SharedPtr Tests Passed -----" << std::endl;
}

void TestSmartPtr() {
    std::cout << "----- SmartPtr Tests -----" << std::endl;

    SmartPtr<TestClass> ptr1;
    assert(ptr1.isNull());
    assert(ptr1.getRefCount() == 0);

    SmartPtr<TestClass> ptr2(new TestClass(20));
    assert(!ptr2.isNull());
    assert(ptr2.getRefCount() == 1);
    assert(ptr2->value == 20);

    SmartPtr<TestClass> ptr3(ptr2);
    assert(ptr2.getRefCount() == 2);
    assert(ptr3.getRefCount() == 2);

    SmartPtr<TestClass> ptr4;
    ptr4 = ptr3;
    assert(ptr3.getRefCount() == 3);
    assert(ptr4.getRefCount() == 3);

    {
        SmartPtr<TestClass> ptr5(ptr2);
        assert(ptr2.getRefCount() == 4);
    }
    assert(ptr2.getRefCount() == 3);

    ptr4 = ptr4; 
    assert(ptr4.getRefCount() == 3);


    std::cout << "----- SmartPtr Tests Passed -----" << std::endl;
}

void TestUniquePtr() {
    std::cout << "----- UniquePtr Tests -----" << std::endl;

    UniquePtr<TestClass> ptr1;
    assert(ptr1.isNull());

    UniquePtr<TestClass> ptr2(new TestClass(30));
    assert(!ptr2.isNull());
    assert(ptr2->value == 30);

    UniquePtr<TestClass> ptr3(std::move(ptr2));
    assert(ptr2.isNull());
    assert(!ptr3.isNull());
    assert(ptr3->value == 30);

    UniquePtr<TestClass> ptr4;
    ptr4 = std::move(ptr3);
    assert(ptr3.isNull());
    assert(!ptr4.isNull());
    assert(ptr4->value == 30);

    TestClass* rawPtr = ptr4.release(); 
    assert(ptr4.isNull());
    assert(rawPtr != nullptr);
    delete rawPtr;

    ptr4.reset(new TestClass(40));
    assert(!ptr4.isNull());
    assert(ptr4->value == 40);


    std::cout << "----- UniquePtr Tests Passed -----" << std::endl;
}

int main() {
    TestSharedPtr();
    TestSmartPtr();
    TestUniquePtr();
    return 0;
}