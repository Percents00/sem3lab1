#pragma once

template <typename T>
class Sequence {
public:
    virtual ~Sequence() = default;

    virtual void push_back(const T& value) = 0;

    virtual void pop_back() = 0;

    virtual T& operator[](size_t index) = 0;

    virtual size_t getSize() const = 0;
};