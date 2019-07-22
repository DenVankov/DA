#ifndef DA_4_VECTOR_H
#define DA_4_VECTOR_H

#include <iostream>
#include <exception>
#include <new>

template<class T>
struct TVector
{
    T* begin;
    int capacity;
    int size;
};

template<class T>
void VectorInit(TVector<T>& vector)
{
    try {
        vector.begin = new T[1];
    }

    catch (const std::bad_alloc& e) {
        printf("ERROR: No memory\n");
        exit(0);
    }

    vector.capacity = 1;
    vector.size = 0;
}

template<class T>
void VectorPushBack(TVector<T>& vector, const T& val)
{
    if (vector.size == vector.capacity) {
        vector.capacity *= 2;
        T* vector2 = nullptr;

        try {
            vector2 = new T[vector.capacity];
        }

        catch (const std::bad_alloc& e) {
            printf("ERROR: No memory\n");
            exit(0);
        }

        for (int i = 0; i < vector.size; ++i) {
            vector2[i] = vector.begin[i];
        }

        delete[] vector.begin;

        vector.begin = vector2;
    }

    vector.begin[vector.size++] = val;
}

template<class T>
void VectorDestroy(TVector<T>& vector)
{
    delete[] vector.begin;
}

#endif //DA_4_VECTOR_H
