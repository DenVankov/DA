    #include "TString.h"

    TString::TString() {
        mStr = new char[1];

        if (!mStr) {
            std::cout << "ERROR: No memory\n";
            exit(0);
        }

        mStr[0] = '\0';
    }


    TString::TString(const char *s) {
        mStr = new char[1];

        if (!mStr) {
            std::cout << "ERROR: No memory\n";
            exit(0);
        }

        mStr[0] = '\0';

        mCopy2(s);
    }

    TString::~TString() {
        delete[] mStr;
    }

    size_t TString::Length() const {
        return strlen(mStr);
    }

    const char* TString::GetStr() const {
        return mStr;
    }

    void TString::Swap(TString &str) {
        char* buff = mStr;
        mStr = str.mStr;
        str.mStr = buff;
    }

    TString& TString::operator=(const TString &str) {
        if (this != &str) {
            mCopy(str);
        }

        return *this;
    }

    bool TString::operator<(const TString& str) const {
        return strcmp(mStr, str.mStr) < 0;
    }

    bool TString::operator==(const TString& str) const {
        return strcmp(mStr, str.mStr) == 0;
    }

    void TString::mCopy(const TString &str) {
        delete[] mStr;
        size_t n = str.Length();
        mStr = new char[n + 1];

        if(!mStr) {
            std::cout << "ERROR: No memory\n";
            exit(0);
        }
        strcpy(mStr, str.mStr);
    }

    void TString::mCopy2(const char *str) {
        delete[] mStr;
        size_t n = strlen(str);
        mStr = new char[n + 1];

        if(!mStr) {
            std::cout << "ERROR: No memory\n";
            exit(0);
        }
        strcpy(mStr, str);

    }