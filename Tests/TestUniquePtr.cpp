#include "../UniquePtr.h"
#include <cassert>
#include <iostream>

void testUniquePtrConstructor() {
    UniquePtr<int> ptr(new int(5));
    assert(*ptr == 5);

    UniquePtr<int> nullPtr;
    assert(nullPtr.isNull());
}

void testUniquePtrMoveConstructor() {
    UniquePtr<int> ptr1(new int(10));
    UniquePtr<int> ptr2(std::move(ptr1));
    assert(*ptr2 == 10);
    assert(ptr1.isNull());
}

void testUniquePtrMoveAssignment() {
    UniquePtr<int> ptr1(new int(20));
    UniquePtr<int> ptr2;
    ptr2 = std::move(ptr1);

    assert(*ptr2 == 20);
    assert(ptr1.isNull());

    UniquePtr<int> ptr3(new int(30));
    ptr2 = std::move(ptr3);

    assert(*ptr2 == 30);
    assert(ptr3.isNull());
}

void testUniquePtrDereference() {
    UniquePtr<int> ptr(new int(50));
    assert(*ptr == 50);
    *ptr = 60;
    assert(*ptr == 60);

}

void testUniquePtrMemberAccess() {
    UniquePtr<int> ptr(new int(42));

    assert(*ptr == 42);
}



void testUniquePtrRelease() {
    UniquePtr<int> ptr(new int(70));
    int* rawPtr = ptr.release();
    assert(ptr.isNull());
    assert(*rawPtr == 70);
    delete rawPtr;
}

void testUniquePtrReset() {
    UniquePtr<int> ptr(new int(80));
    ptr.reset(new int(90));
    assert(*ptr == 90);
    ptr.reset();
    assert(ptr.isNull());
}


void runUniquePtrTest() {
    testUniquePtrConstructor();
    testUniquePtrMoveConstructor();
    testUniquePtrMoveAssignment();
    testUniquePtrDereference();
    testUniquePtrMemberAccess();
    testUniquePtrRelease();
    testUniquePtrReset();

    std::cout << "UniquePtr tests functionality passed\n";
}