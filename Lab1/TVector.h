#ifndef UNTITLED1_TVECTOR_H
#define UNTITLED1_TVECTOR_H

#include <iostream>
#include <cstddef>
#include <cstdlib>

struct TData{
    char *key;
    char *value;
};

class TVector {
public:
    TVector(int size, int capacity);
    void PushBack(TData elem);
    void Print();
    int Size() const;
    TData &operator[](int index) const;
    ~TVector();

private:
    TData *arr;
    int size;
    int capacity;
};

#endif //UNTITLED1_TVECTOR_H
