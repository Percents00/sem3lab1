#include "MutableSequence.h"
#include "LinkedList.h"
#include "SharedPtr.h"

template <typename T>
class MutableListSequence : public MutableSequence<T> {
private:
    LinkedList<T>* list;
public:
    MutableListSequence() : list(new LinkedList<T>()) {}

    MutableListSequence(const SharedPtr<T>* items, int count) : list(new LinkedList<T>(items, count)) {}



    MutableListSequence(const MutableListSequence<T>& other) : list(new LinkedList<T>(*other.list)) {}

    MutableListSequence<T>& operator=(const MutableListSequence<T>& other) {
        if (this != &other) {
            delete list;
            list = new LinkedList<T>(*other.list);
        }
        return *this;
    }


    ~MutableListSequence() override {
        delete list;
    }

    void Append(const SharedPtr<T>& item) override {
        list->Append(item);
    }

    void Prepend(const SharedPtr<T>& item) override {
        list->Prepend(item);
    }


    MutableListSequence<T>* GetSubSequence(int startIndex, int endIndex)  override {
        return new MutableListSequence<T>(list->GetSubList(startIndex, endIndex));
    }


    void InsertAt(int index, const SharedPtr<T>& item) override {
        list->InsertAt(index, item);
    }

    SharedPtr<T>& GetFirst() const override {
        return list->GetFirst();
    }

    SharedPtr<T>& GetLast() const override {
        return list->GetLast();
    }

    SharedPtr<T>& Get(int index) const override {
        return list->Get(index);
    }

    int GetLength() const override {
        return list->GetLength();
    }



    void Concatenate(MutableSequence<T>* other) override
    {
      for(int i = 0; i < other->GetLength(); i++)
      {
          Append(other->Get(i));
      }
    }



};