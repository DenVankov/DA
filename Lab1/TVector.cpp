#include <iostream>
#include "TVector.h"

TVector::TVector(int size, int capacity) {
    this->size = size;
    this->capacity = capacity;
    arr = new TData[capacity];
}

void TVector::PushBack(TData elem) {
    if (capacity == size)
    {
        capacity *= 2;
        arr = (TData *)realloc(arr, sizeof(TData) * capacity);
    }
    arr[size++] = elem;

}

int TVector::Size() const {
    return size;
}

void TVector::Print() {
    for(int i = 0; i < size; ++i)
    {
        std::cout << arr[i].key << '\t' << arr[i].value << '\n';
    }
}

TData &TVector::operator[](int index) const {
    return arr[index];
}
TVector::~TVector() {
    for (int i = 0; i < size; ++i) {
        delete this->arr[i].key;
        delete this->arr[i].value;
    }
    delete[] arr;
}