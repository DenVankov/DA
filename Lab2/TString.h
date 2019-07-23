#ifndef DA2_STRING_H
#define DA2_STRING_H

#ifndef TSTRING_H
#define TSTRING_H

#include <exception>
#include <new>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

class TString
{
public:
    TString();
    TString(const char* s);
    ~TString();

    size_t Length() const;
    const char* GetStr() const;
    void Swap(TString &str);

    TString& operator=(const TString &str);
    bool operator<(const TString &str) const;
    bool operator==(const TString &str) const;

private:
    char* mStr;

    void mCopy(const TString &str);
    void mCopy2(const char* str);
};

#endif
#endif //DA2_STRING_H
