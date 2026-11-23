#ifndef BASICCONTAINER_CPP
#define BASICCONTAINER_CPP

#include <iostream>
#include <cstdlib>

template <typename T>
BasicContainer<T>::BasicContainer(int initCapacity) {
    if (initCapacity <= 0) {
        initCapacity = 16;
    }

    capacity = initCapacity;
    used = 0;
    data = new T[capacity];
}

template <typename T>
BasicContainer<T>::~BasicContainer() {
    delete[] data;
}

template <typename T>
BasicContainer<T>::BasicContainer(const BasicContainer<T>& other) {
    capacity = other.capacity;
    used = other.used;
    data = new T[capacity];

    for (int i = 0; i < used; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
BasicContainer<T>& BasicContainer<T>::operator=(const BasicContainer<T>& other) {
    if (this != &other) {
        delete[] data;

        capacity = other.capacity;
        used = other.used;
        data = new T[capacity];

        for (int i = 0; i < used; i++) {
            data[i] = other.data[i];
        }
    }

    return *this;
}

template <typename T>
bool BasicContainer<T>::empty() const {
    return used == 0;
}

template <typename T>
int BasicContainer<T>::size() const {
    return used;
}

template <typename T>
void BasicContainer<T>::resize(int newCapacity) {
    T* temp = new T[newCapacity];

    for (int i = 0; i < used; i++) {
        temp[i] = data[i];
    }

    delete[] data;
    data = temp;
    capacity = newCapacity;
}

template <typename T>
void BasicContainer<T>::push_back(const T& x) {
    if (used == capacity) {
        resize(2 * used + 1);
    }

    data[used] = x;
    used++;
}

template <typename T>
void BasicContainer<T>::pop_back() {
    if (used > 0) {
        used--;
    }
}

template <typename T>
T& BasicContainer<T>::back() {
    if (used == 0) {
        std::cerr << "Error: empty container." << std::endl;
        exit(1);
    }

    return data[used - 1];
}

template <typename T>
const T& BasicContainer<T>::back() const {
    if (used == 0) {
        std::cerr << "Error: empty container." << std::endl;
        exit(1);
    }

    return data[used - 1];
}

template <typename T>
void BasicContainer<T>::print(std::ostream& os, char ofc) const {
    for (int i = 0; i < used; i++) {
        os << data[i];

        if (ofc != '\0' && i < used - 1) {
            os << ofc;
        }
    }
}

#endif