#ifndef GENERICSTACK_CPP
#define GENERICSTACK_CPP

#include <iostream>
#include <new>

template <typename T>
GenericStack<T>::GenericStack() : container(16) {
}

template <typename T>
GenericStack<T>::~GenericStack() {
}

template <typename T>
GenericStack<T>::GenericStack(const GenericStack<T>& other) : container(other.container) {
}

template <typename T>
GenericStack<T>& GenericStack<T>::operator=(const GenericStack<T>& other) {
    if (this != &other) {
        container = other.container;
    }

    return *this;
}

template <typename T>
bool GenericStack<T>::empty() const {
    return container.empty();
}

template <typename T>
void GenericStack<T>::push(const T& x) {
    try {
        container.push_back(x);
    }
    catch (std::bad_alloc&) {
        std::cerr << "Error: not enough memory to push element onto stack." << std::endl;
    }
}

template <typename T>
void GenericStack<T>::pop() {
    if (empty()) {
        std::cerr << "Error: cannot pop from an empty stack." << std::endl;
        return;
    }

    container.pop_back();
}

template <typename T>
T& GenericStack<T>::top() {
    if (empty()) {
        std::cerr << "Error: cannot access top of an empty stack." << std::endl;
        exit(1);
    }

    return container.back();
}

template <typename T>
const T& GenericStack<T>::top() const {
    if (empty()) {
        std::cerr << "Error: cannot access top of an empty stack." << std::endl;
        exit(1);
    }

    return container.back();
}

template <typename T>
int GenericStack<T>::size() const {
    return container.size();
}

template <typename T>
void GenericStack<T>::print(std::ostream& os, char ofc) const {
    GenericStack<T> copy(*this);

    while (!copy.empty()) {
        os << copy.top();
        copy.pop();

        if (ofc != '\0' && !copy.empty()) {
            os << ofc;
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const GenericStack<T>& a) {
    a.print(os);
    return os;
}

template <typename T>
bool operator==(const GenericStack<T>& a, const GenericStack<T>& b) {
    if (a.size() != b.size()) {
        return false;
    }

    GenericStack<T> copyA(a);
    GenericStack<T> copyB(b);

    while (!copyA.empty()) {
        if (!(copyA.top() == copyB.top())) {
            return false;
        }

        copyA.pop();
        copyB.pop();
    }

    return true;
}

template <typename T>
bool operator<(const GenericStack<T>& a, const GenericStack<T>& b) {
    if (a.size() != b.size()) {
        return false;
    }

    GenericStack<T> copyA(a);
    GenericStack<T> copyB(b);

    while (!copyA.empty()) {
        if (!(copyA.top() < copyB.top())) {
            return false;
        }

        copyA.pop();
        copyB.pop();
    }

    return true;
}

#endif