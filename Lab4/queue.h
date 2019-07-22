#ifndef DA_4_QUEUE_H
#define DA_4_QUEUE_H

#include <iostream>
#include <new>
#include <exception>

template<class T>
struct TQueue
{
    T* begin;
    int capacity;
    int size;
    int offset;
};

template<class T>
void QueueInit(TQueue<T>& q, int size)
{
    try {
        q.begin = new T[size];
    }

    catch (const std::bad_alloc& e) {
        printf("ERROR: No memory\n");
        exit(0);
    }

    q.capacity = size;
    q.size = 0;
    q.offset = 0;
}

template<class T>
void QueuePush(TQueue<T>& q, const T& val)
{
    q.begin[(q.offset + q.size++) % q.capacity] = val;
}

template<class T>
void QueuePop(TQueue<T>& q)
{
    q.offset = (q.offset + 1) % q.capacity;
    --q.size;
}

template<class T>
void QueueDestroy(TQueue<T>& q)
{
    delete[] q.begin;
}

#endif //DA_4_QUEUE_H
