#include <iostream>
#include <cstring>
#include <cmath>

#include "TVector.h"


void CountSort(int i, TVector &v) {
    TVector res(0, v.Size() );
    int C[16];

    for (int j = 0; j< 16; ++j){
        C[j] = 0;
    }

    for (int j = v.Size() - 1; j >= 0; --j) {
        if(v[j].key[i] -'0' > 15) {
            C[v[j].key[i] - '0' - 39] += 1;
        }
        else C[v[j].key[i] - '0'] += 1;
    }

    for (int j = 1; j < 16; ++j) {
        C[j] += C[j-1];
    }

    for (int j = v.Size() - 1; j >= 0; --j) {
        if(v[j].key[i] -'0' > 15) {
            C[v[j].key[i] - '0' - 39] -= 1;
            res[C[v[j].key[i] - '0' - 39]] = v[j];
        }
        else {
            C[v[j].key[i] - '0'] -= 1;
            res[C[v[j].key[i] - '0']] = v[j];
        }
    }

    for (int j = 0; j < v.Size(); ++j) {
        v[j] = res[j];
    }

}

void RadixSort(TVector &v) {
    for (int i = 31; i >= 0; --i) {
        CountSort(i, v);
    }
}

int main()
{
    TVector v(0, 10);
    TData elem;
    elem.key = new char[32 + 1];
    while (scanf("%s", elem.key) == 1)
    {
        elem.value = new char[2048 + 1];

        scanf("%s", elem.value);
        elem.value = (char *)realloc(elem.value, sizeof(char) * (strlen(elem.value) + 1)); 
        v.PushBack(elem);
        elem.key = new char[32 + 1];
    }
    delete elem.key;
    RadixSort(v);
    v.Print();

    return 0;
}
