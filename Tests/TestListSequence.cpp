#include "../ListSequence.h"
#include <cassert>
#include <iostream>

void testListSequenceAppend() {
    ListSequence<int> seq;
    SharedPtr<int> val1(new int(1));
    SharedPtr<int> val2(new int(2));
    seq.Append(val1);
    seq.Append(val2);
    assert(seq.GetLength() == 2);
    assert(*seq.GetFirst() == 1);
    assert(*seq.GetLast() == 2);
}

void testListSequencePrepend() {
    ListSequence<int> seq;
    SharedPtr<int> val1(new int(1));
    SharedPtr<int> val2(new int(2));
    seq.Prepend(val1);
    seq.Prepend(val2);
    assert(seq.GetLength() == 2);
    assert(*seq.GetFirst() == 2);
    assert(*seq.GetLast() == 1);
}

void testListSequenceInsertAt() {
    ListSequence<int> seq;
    SharedPtr<int> val1(new int(1));
    SharedPtr<int> val2(new int(2));
    SharedPtr<int> val3(new int(3));
    seq.Append(val1);
    seq.Append(val2);
    seq.InsertAt(1, val3);
    assert(seq.GetLength() == 3);
    assert(*seq.Get(0) == 1);
    assert(*seq.Get(1) == 3);
    assert(*seq.Get(2) == 2);

    seq.InsertAt(0, val3);
    assert(seq.GetLength() == 4);
    assert(*seq.GetFirst() == 3);


    ListSequence<int> emptySeq;
    emptySeq.InsertAt(0, val1);
    assert(emptySeq.GetLength() == 1);
    assert(*emptySeq.GetFirst() == 1);
}

void testListSequenceGetSubSequence() {
    ListSequence<int> seq;
    for (int i = 1; i <= 5; ++i) {
        seq.Append(SharedPtr<int>(new int(i)));
    }

    auto subseq = seq.GetSubSequence(1, 3);
    assert(subseq->GetLength() == 3);
    assert(*subseq->Get(0) == 2);
    assert(*subseq->Get(1) == 3);
    assert(*subseq->Get(2) == 4);

    subseq = seq.GetSubSequence(0, 4);
    assert(subseq->GetLength() == 5);

    subseq = seq.GetSubSequence(0, 0);
    assert(subseq->GetLength() == 1);
    assert(*subseq->Get(0) == 1);
}


void testListSequenceCopyConstructor(){
    SharedPtr<int> val1 = SharedPtr<int>(new int(1));
    SharedPtr<int> val2 = SharedPtr<int>(new int(2));

    ListSequence<int> seq1;
    seq1.Append(val1);
    seq1.Append(val2);

    ListSequence<int> seq2(seq1);


    assert(seq1.GetLength() == 2);
    assert(*seq1.Get(0) == 1);
    assert(*seq1.Get(1) == 2);

    assert(seq2.GetLength() == 2);
    assert(*seq2.Get(0) == 1);
    assert(*seq2.Get(1) == 2);

}


void runListSequenceTest() {
    testListSequenceAppend();
    testListSequencePrepend();
    testListSequenceInsertAt();
    testListSequenceGetSubSequence();
    testListSequenceCopyConstructor();

    std::cout << "ListSequence tests functionality passed\n";
}