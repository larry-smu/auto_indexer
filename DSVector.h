#ifndef INC_20F_AUTO_IDX_DSVECTOR_H
#define INC_20F_AUTO_IDX_DSVECTOR_H

#include <stdexcept>
#include <iostream>
#include <algorithm>

template <typename T>
class DSVector {
private:
    T* vector;
    int length;
    int capacity;

public:
    DSVector();
    ~DSVector();
    DSVector(const DSVector &vector);

    void append(T); //Append
    int search(T); //Search by data
    T& at(int); //Search by index
    void removeElement(T); //Remove by data
    int getLength(); //Return length
    bool isEmpty(); //Check if vector is empty
    void sort(); //sorting

    T operator[] (int);
    DSVector<T>& operator= (const DSVector&);
};

/**
 * Rule of 3
 */

template <typename T>
DSVector<T>::DSVector() {
    length = 0;
    capacity = 40;
    vector = new T[capacity];
}

template <typename T>
DSVector<T>::~DSVector() {
    delete [] vector;
}

template <typename T>
DSVector<T>::DSVector(const DSVector<T> &v) {
    length = v.length;
    vector = new T[v.capacity];

    for(int i = 0; i < v.length; ++i) {
        vector[i] = v.vector[i];
    }
}

/**
 * Functions
 */
template <typename T>
void DSVector<T>::append(const T data) {
    ++length;
    if(length == capacity) capacity *= 2;
    T* temp = new T[capacity];
    for(int i = 0; i < length-1; ++i) temp[i] = vector[i];
    temp[length-1] = data;
    delete [] vector;
    vector = temp;
}

template <typename T>
int DSVector<T>::search(T data) {
    for(int i = 0; i < length; ++i) {
        if(vector[i] == data)
            return i;
    }
    return -1;
}

template <typename T>
T& DSVector<T>::at(int index) {
    if(index < 0 || index > length)
        throw std::out_of_range ("out of range");
    else
        return vector[index];
}

template <typename T>
void DSVector<T>::removeElement(T ele) {
    for(int i = 0; i < length; ++i) {
        if(vector[i] == ele) {
            if(i == length -1) break;
            for(int j = i; j < length; ++j) {
                vector[j] = vector[j+1];
            }
        }
    }

    //Remove the last index
    vector[length-1] = '\0';
    --length;
}

template <typename T>
int DSVector<T>::getLength() {
    return length;
}

template <typename T>
bool DSVector<T>::isEmpty() {
    return length == 0;
}

template <typename T>
void DSVector<T>::sort() {

    std::sort(vector, vector+length);
//
//    for(int i = 0; i < length; ++i) {
//        for(int j = 0; j < length; ++j) {
//            T cur = vector[j];
//            T prev = vector[j-1];
//
//            if(prev >= cur) {
//                vector[j] = prev;
//                vector[j-1] = cur;
//            }
//        }
//    }
}

/**
 * Operators
 */

template <typename T>
T DSVector<T>::operator[] (int index) {
    return vector[index];
}

template<typename T>
DSVector<T> &DSVector<T>::operator=(const DSVector<T> &v) {
    length = v.length;
    capacity = v.capacity;

    for(int i = 0; i < v.length; ++i) {
        vector[i] = v.vector[i];
    }

    return *this;
}

#endif //INC_20F_AUTO_IDX_DSVECTOR_H