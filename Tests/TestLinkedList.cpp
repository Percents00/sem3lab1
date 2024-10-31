#include "../LinkedList.h"
#include <cassert>
#include <iostream>

void testAppend() {
    LinkedList<int> list;
    SharedPtr<int> val1(new int(1));
    SharedPtr<int> val2(new int(2));
    list.Append(val1);
    list.Append(val2);
    assert(list.GetLength() == 2);
    assert(*list.GetFirst() == 1);
    assert(*list.GetLast() == 2);
}

void testPrepend() {
    LinkedList<int> list;
    SharedPtr<int> val1(new int(1));
    SharedPtr<int> val2(new int(2));
    list.Prepend(val1);
    list.Prepend(val2);
    assert(list.GetLength() == 2);
    assert(*list.GetFirst() == 2);
    assert(*list.GetLast() == 1);
}


void testInsertAt() {
    LinkedList<int> list;
    SharedPtr<int> val1(new int(1));
    SharedPtr<int> val2(new int(2));
    SharedPtr<int> val3(new int(3));
    list.Append(val1);
    list.Append(val2);
    list.InsertAt(1, val3);
    assert(list.GetLength() == 3);
    assert(*list.Get(0) == 1);
    assert(*list.Get(1) == 3);
    assert(*list.Get(2) == 2);

    list.InsertAt(0, val3);
    assert(list.GetLength() == 4);
    assert(*list.GetFirst() == 3);


    LinkedList<int> emptyList;
    emptyList.InsertAt(0, val1);
    assert(emptyList.GetLength() == 1);
    assert(*emptyList.GetFirst() == 1);
}


void testGetFirst()
{
    LinkedList<int> list;
    SharedPtr<int> val1 = SharedPtr<int>(new int(5));
    list.Append(val1);
    assert(*list.GetFirst() == 5);
}


void testGetLast()
{
    LinkedList<int> list;
    SharedPtr<int> val1 = SharedPtr<int>(new int(5));
    list.Append(val1);
    assert(*list.GetLast() == 5);
}

void testGetByIndex() {
    LinkedList<int> list;
    SharedPtr<int> val1(new int(1));
    SharedPtr<int> val2(new int(2));

    list.Append(val1);
    list.Append(val2);

    assert(*list.Get(0) == 1);
    assert(*list.Get(1) == 2);
}

void testSubList() {
    LinkedList<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.Append(SharedPtr<int>(new int(i)));
    }

    LinkedList<int> sublist = list.GetSubList(1, 3);
    assert(sublist.GetLength() == 3);
    assert(*sublist.Get(0) == 2);
    assert(*sublist.Get(1) == 3);
    assert(*sublist.Get(2) == 4);

    sublist = list.GetSubList(0, 4);
    assert(sublist.GetLength() == 5);

    sublist = list.GetSubList(0, 0);
    assert(sublist.GetLength() == 1);
    assert(*sublist.Get(0) == 1);
}

void testAssignmentOperator()
{

    LinkedList<int> list1;
    list1.Append(SharedPtr<int>(new int(1)));
    list1.Append(SharedPtr<int>(new int(2)));

    LinkedList<int> list2;
    list2 = list1;

    assert(list2.GetLength() == 2);
    assert(*list2.Get(0) == 1);
    assert(*list2.Get(1) == 2);


    LinkedList<int> list3;
    list3.Append(SharedPtr<int>(new int(3)));
    list3 = list1;

    assert(list3.GetLength() == 2);
    assert(*list3.Get(0) == 1);
    assert(*list3.Get(1) == 2);

}

void runLinkedListTest() {
    testAppend();
    testPrepend();
    testInsertAt();
    testGetFirst();
    testGetLast();
    testGetByIndex();
    testSubList();
    testAssignmentOperator();
    std::cout << "LinkedList functionality tests passed\n";
}
