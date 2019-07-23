#ifndef DA6_TBIGINT_H
#define DA6_TBIGINT_H

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

const int BASE_POW = 4;
const int BASE = 10000;

class TBigInt {
public:
    TBigInt() {};
    TBigInt(const std::string &str);
    TBigInt(const size_t &size);
    TBigInt(int size);
    ~TBigInt() {};

    TBigInt operator+(const TBigInt &obj);
    TBigInt operator-(const TBigInt &obj);
    TBigInt operator*(const TBigInt &obj);
    TBigInt operator/(TBigInt &obj);
    TBigInt Power(int deg);
    bool operator<(const TBigInt &obj) const;
    bool operator>(const TBigInt &obj) const;
    bool operator==(const TBigInt &obj) const;

    friend std::ostream& operator<< (std::ostream& os, const TBigInt &obj);

    inline size_t size() const
    {
        return mData.size();
    }
    int Get(size_t i) const
    {
        return mData[i];
    };
    void Set(size_t i, int num)
    {
        mData[i] = num;
    };
private:
    std::vector<int> mData;
    void DeleteZeros();
};

#endif //DA6_TBIGINT_H