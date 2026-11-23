#ifndef BASICCONTAINER_H
#define BASICCONTAINER_H

#include <iostream>

template <typename T>
class BasicContainer {
public:
    BasicContainer(int initCapacity = 16);
    ~BasicContainer();

    BasicContainer(const BasicContainer<T>& other);
    BasicContainer<T>& operator=(const BasicContainer<T>& other);

    bool empty() const;
    int size() const;

    void push_back(const T& x);
    void pop_back();

    T& back();
    const T& back() const;

    void print(std::ostream& os, char ofc = '\0') const;

private:
    T* data;
    int used;
    int capacity;

    void resize(int newCapacity);
};

#include "BasicContainer.cpp"

#endif