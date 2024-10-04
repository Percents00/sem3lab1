#include "SharedPtr.h"

template <typename T>
class MutableSequence {
public:

    virtual ~MutableSequence() = default;

    virtual SharedPtr<T>& Get(int index) const = 0;
    virtual SharedPtr<T>& GetFirst() const = 0;
    virtual SharedPtr<T>& GetLast() const = 0;

    virtual int GetLength() const = 0;
    virtual void Append(const SharedPtr<T>& item) = 0;
    virtual void Prepend(const SharedPtr<T>& item) = 0;
    virtual void InsertAt(int index, const SharedPtr<T>& item) = 0;
    virtual void Concatenate(MutableSequence<T> *sequence) = 0;

    virtual MutableSequence<T> *GetSubSequence(int startIndex, int endIndex) = 0;
};
