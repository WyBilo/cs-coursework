#ifndef GENERICSTACK_H
#define GENERICSTACK_H

#include <iostream>
#include "BasicContainer.h"

template <typename T>
class GenericStack {
public:
    GenericStack();
    ~GenericStack();

    GenericStack(const GenericStack<T>& other);
    GenericStack<T>& operator=(const GenericStack<T>& other);

    bool empty() const;
    void push(const T& x);
    void pop();

    T& top();
    const T& top() const;

    int size() const;

    void print(std::ostream& os, char ofc = '\0') const;

private:
    BasicContainer<T> container;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const GenericStack<T>& a);

template <typename T>
bool operator==(const GenericStack<T>& a, const GenericStack<T>& b);

template <typename T>
bool operator<(const GenericStack<T>& a, const GenericStack<T>& b);

#include "GenericStack.cpp"

#endif