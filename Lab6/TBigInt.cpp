#include "TBigInt.h"

TBigInt::TBigInt(const std::string &str)
{
    for (int i = str.size() - 1; i >= 0; --i) {
        int tmp = 0;
        for (int j = 0;  i >= 0 && j < BASE_POW; ++j, --i) {
            tmp = tmp + (str[i] - '0') * pow(10, j);
        }
        ++i;
        mData.push_back(tmp);
    }
    DeleteZeros();
}

TBigInt::TBigInt(const size_t &size)
{
    mData.resize(size, 0);
}

TBigInt::TBigInt(int size)
{
    if (!size) {
        mData.push_back(0);
    } else {
        while (size) {
            mData.push_back(size % BASE);
            size /= BASE;
        }
    }
}

void TBigInt::DeleteZeros()
{
    while (mData.size() > 1 && mData.back() == 0 ) {
        mData.pop_back();
    }
}

bool TBigInt::operator==(const TBigInt &obj) const
{
    return mData == obj.mData;
}

bool TBigInt::operator<(const TBigInt &obj) const
{
    size_t n = mData.size();
    if (n!= obj.mData.size())
        return n < obj.mData.size();
    for (int i = n - 1; i >= 0; --i) {
        if(mData[i] != obj.mData[i])
            return mData[i] < obj.mData[i];
    }
    return false;

}

bool TBigInt::operator>(const TBigInt &obj) const
{
    size_t n = mData.size();
    if (n!= obj.mData.size())
        return n > obj.mData.size();
    for (int i = n - 1; i >= 0; --i) {
        if(mData[i] != obj.mData[i])
            return mData[i] > obj.mData[i];
    }

    return false;
}

TBigInt TBigInt::Power(int deg)
{
    if (deg == 0) {
        return TBigInt("1");
    }
    if (deg % 2 == 0) {
        TBigInt res = (*this).Power(deg / 2);
        return res * res;
    } else {
        TBigInt res = (* this).Power(deg - 1);
        return (*this) * res;
    }
}

TBigInt TBigInt::operator+(const TBigInt &obj)
{
    int l = 0;
    int r = 0;
    size_t maxLen = std::max(mData.size(), obj.mData.size());
    TBigInt result(maxLen + 1);
    for (size_t i = 0; i < maxLen; ++i) {
        if (mData.size() <= i) {
            l = obj.Get(i);
        } else if (obj.mData.size() <= i) {
            l = mData[i];
        } else {
            l = mData[i] + obj.Get(i);
        }
        l += r;
        result.Set(i, l % BASE);
        r = l / BASE;
    }
    if (r != 0)
        result.Set(maxLen, r);
    result.DeleteZeros();
    return result;
}

TBigInt TBigInt::operator-(const TBigInt &obj)
{
    int l = 0;
    int r = 0;
    int balance = 0;
    TBigInt result(mData.size());
    for (int i = 0; i < mData.size(); ++i) {
        r = i < obj.size() ? obj.Get(i) : 0;
        l = mData[i] - r + balance;
        balance = l < 0 ? -1 : 0;
        result.Set(i, l < 0 ? l + BASE : l);
    }
    result.DeleteZeros();
    return result;
}

TBigInt TBigInt::operator*(const TBigInt &obj)
{
    size_t sizeLeft = mData.size();
    size_t sizeRight = obj.mData.size();
    TBigInt result(sizeLeft + sizeRight);
    for (int i = 0; i < sizeRight; ++i) {
        if(obj.mData[i] == 0)
            continue;
        int balance = 0;
        for (int j = 0; j < sizeLeft; ++j) {
            int tmp = mData[j] * obj.mData[i] + result.mData[i + j] + balance;
            balance = tmp / BASE;
            result.mData[i + j] = tmp % BASE;
        }
        result.Set(i + sizeLeft, balance);
    }
    result.DeleteZeros();
    return result;
}

TBigInt TBigInt::operator/(TBigInt &obj)
{
    int d = BASE/(obj.mData.back() + 1);
    TBigInt u = *this * d;
    TBigInt v = obj * d;
    size_t uSize = u.mData.size();
    TBigInt q(uSize);
    TBigInt r;
    for (int i = uSize - 1; i >= 0; --i) {
        r = r * BASE + u.mData[i];
        int num1 = r.mData.size() <= v.mData.size() ? 0 : r.Get(v.mData.size());
        int num2 = r.mData.size() <= v.mData.size() - 1 ? 0 : r.Get(v.mData.size() - 1);
        int q2 = (num1 * BASE + num2) / v.mData.back();
        TBigInt tmp = v * q2;

        while (tmp > r) {
            tmp = tmp - v;
            --q2;
        }
        r = r - tmp;
        q.mData[i] = q2;
    }
    q.DeleteZeros();
    return q;
}

std::ostream& operator<<(std::ostream &os, const TBigInt &obj)
{
    int size = obj.mData.size();
    if (!size)
        return os;
    os << obj.mData[size - 1];
    for (int i = size - 2; i >= 0; --i)
        os << std::setfill('0') << std::setw(BASE_POW) << obj.mData[i];

    return os;
}