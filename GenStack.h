/*
 * GenStack.h
 *
 *  Created on: Mar 27, 2020
 *  Own stack class based on arrays
 */

#ifndef GENSTACK_H_
#define GENSTACK_H_

#include <iostream>
using namespace std;

#define DEFAULT_SIZE 128

template<class T>
class GenStack {
public:
    GenStack();
    GenStack(int maxCapacity);
    ~GenStack();

    void push(const T& d);
    const T& top();
    T& pop();
    int size() const;
    bool empty() const;

private:
    int _cappacity; // Max size of Stack
    int _top;
    T *_data; // Array store all element of stack
};

/**
 * Default constructor.
 */
template<class T>
GenStack<T>::GenStack() {
    _data = new T[DEFAULT_SIZE];
    _cappacity = DEFAULT_SIZE;
    _top = -1;
}

/**
 * Constructor with maximum element of stack
 */
template<class T>
GenStack<T>::GenStack(int maxCappacity) {
    _data = new T[maxCappacity];
    _cappacity = maxCappacity;
    _top = -1;
}

/**
 * Destructor.
 */
template<class T>
GenStack<T>::~GenStack() {
    delete[] _data;
    _top = -1;
    _cappacity = 0;
}

template<class T>
void GenStack<T>::push(const T& d) {
    // In-case stack is full
    if (_cappacity == size()) {
        // Need to reallocate all data. And double size of stack
        T* tmpData = new T[_cappacity];
        for (int i = 0; i < _cappacity; i++) {
            tmpData[i] = _data[i];
        }
        delete[] _data;
        // Re allocate data array
        int new_cappacity = _cappacity * 2;
        _data = new T[new_cappacity];
        for (int i = 0; i < _cappacity; i++) {
            _data[i] = tmpData[i];
        }
        _cappacity = new_cappacity;
        _data[++_top] = d;
        // deallocated tmp data
        delete[] tmpData;
    } else {
        // In-case normal. Just increase the top index and assign the data
        _data[++_top] = d;
    }
}

template<class T>
const T& GenStack<T>::top() {
    if (empty()) {
        cout << "Stack is empty" << endl;
        throw 1;
    }
    return _data[_top];
}

template<class T>
T& GenStack<T>::pop() {
    if (empty()) {
        cout << "Stack is empty" << endl;
        throw 2;
    }
    return _data[_top--];
}

template<class T>
int GenStack<T>::size() const {
    return (_top + 1);
}

template<class T>
bool GenStack<T>::empty() const {
    return (_top < 0);
}

#endif /* GENSTACK_H_ */
