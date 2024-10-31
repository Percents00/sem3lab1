#include "../SharedPtr.h"
#include <cassert>
#include <iostream>

void testSharedPtrConstructor() {
    SharedPtr<int> ptr(new int(5));
    assert(*ptr == 5);
    assert(ptr.use_count() == 1);

    SharedPtr<int> nullPtr;
    assert(nullPtr.isNull());
    assert(nullPtr.use_count() == 0);
}

void testSharedPtrCopyConstructor() {
    SharedPtr<int> ptr1(new int(10));
    SharedPtr<int> ptr2(ptr1);
    assert(*ptr1 == 10);
    assert(*ptr2 == 10);
    assert(ptr1.use_count() == 2);
    assert(ptr2.use_count() == 2);
}

void testSharedPtrCopyAssignment() {
    SharedPtr<int> ptr1(new int(20));
    SharedPtr<int> ptr2;
    ptr2 = ptr1;
    assert(*ptr1 == 20);
    assert(*ptr2 == 20);
    assert(ptr1.use_count() == 2);
    assert(ptr2.use_count() == 2);


    SharedPtr<int> ptr3(new int(30));
    ptr2 = ptr3;
    assert(*ptr2 == 30);
    assert(*ptr3 == 30);
    assert(ptr3.use_count() == 2);
    assert(ptr1.use_count() == 1);

}

void testSharedPtrMoveConstructor() {
    SharedPtr<int> ptr1(new int(40));
    SharedPtr<int> ptr2(std::move(ptr1));
    assert(*ptr2 == 40);
    assert(ptr2.use_count() == 1);
    assert(ptr1.isNull());
    assert(ptr1.use_count() == 0);
}


void testSharedPtrMoveAssignment() {
    SharedPtr<int> ptr1(new int(50));
    SharedPtr<int> ptr2;
    ptr2 = std::move(ptr1);
    assert(*ptr2 == 50);
    assert(ptr2.use_count() == 1);
    assert(ptr1.isNull());
    assert(ptr1.use_count() == 0);

    SharedPtr<int> ptr3(new int(60));
    ptr2 = std::move(ptr3);

    assert(*ptr2 == 60);
    assert(ptr2.use_count() == 1);
    assert(ptr3.isNull());
    assert(ptr3.use_count() == 0);

}


void testSharedPtrDereference() {
    SharedPtr<int> ptr(new int(70));
    assert(*ptr == 70);
    *ptr = 80;
    assert(*ptr == 80);
}

void testSharedPtrMemberAccess() {
    SharedPtr<int> ptr(new int(90));
    assert(*ptr == 90);


}



void testSharedPtrMultipleReferences() {
    SharedPtr<int> ptr1(new int(100));
    SharedPtr<int> ptr2 = ptr1;
    SharedPtr<int> ptr3 = ptr1;
    assert(ptr1.use_count() == 3);
    assert(ptr2.use_count() == 3);
    assert(ptr3.use_count() == 3);
}




void runSharedPtrTest() {
    testSharedPtrConstructor();
    testSharedPtrCopyConstructor();
    testSharedPtrCopyAssignment();
    testSharedPtrMoveConstructor();
    testSharedPtrMoveAssignment();
    testSharedPtrDereference();
    testSharedPtrMemberAccess();
    testSharedPtrMultipleReferences();
    std::cout << "SharedPtr tests functionality passed\n";
}