#include <exception>
#include <new>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include "vector.h"
#include "queue.h"

void PreBmBc(char* pattern, int m, int* bmBc, int size);
void Suffixes(char* x, int m, int* suff);
void PreBmGs(char* x, int m, int* bmGs, int* suff);
void ApostGian(const TVector<char> &pattern);

int Max(int a, int b)
{
    return a > b ? a : b;
}

struct TPosition
{
    int row;
    int col;
};

int main()
{
    int ch;
    TVector<char> pattern;

    VectorInit<char>(pattern);

    while ((ch = getchar()) != '\n')
    {
        ch = (char)tolower(ch);

        if (ch == ' ')
            ch = '{';

        VectorPushBack<char>(pattern, ch);
    }

    ApostGian(pattern);

    VectorDestroy<char>(pattern);

    return 0;
}

void PreBmBc(char* pattern, int m, int* bmBc, int size)
{
    for (int i = 0; i < size; ++i) {
        bmBc[i] = m;
    }

    for (int i = 0; i < m - 1; ++i) {
        bmBc[pattern[i] - 'a'] = m - i - 1;
    }
}

void Suffixes(char* x, int m, int* suff)
{
    int f = 0;
    int g, i;

    suff[m - 1] = m;
    g = m - 1;

    for (i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g) {
            suff[i] = suff[i + m - 1 - f];
        } else {
            if (i < g) {
                g = i;
            }

            f = i;

            while (g >= 0 && x[g] == x[g + m - 1 - f]) {
                --g;
            }

            suff[i] = f - g;
        }
    }
}

void PreBmGs(char* x, int m, int* bmGs, int* suff)
{
    int i, j;

    Suffixes(x, m, suff);

    for (i = 0; i < m; ++i) {
        bmGs[i] = m;
    }

    for (i = m - 1; i >= -1; --i) {
        if (i == -1 || suff[i] == i + 1) {
            for (j = 0; j < m - 1 - i; ++j) {
                if (bmGs[j] == m) {
                    bmGs[j] = m - 1 - i;
                }
            }
        }
    }

    for (i = 0; i < m - 1; ++i) {
        bmGs[m - 1 - suff[i]] = m - 1 - i;
    }
}

void ApostGian(const TVector<char> &pattern)
{
    const int A_SIZE = '{' - 'a' + 1;

    int i, k, s, shift, ch;

    int* bmBc = nullptr;
    int* bmGs = nullptr;
    int* skip = nullptr;
    int* suff = nullptr;
    TQueue<char> text;
    TQueue<TPosition> pos;
    TPosition tmpPos;

    try {
        bmBc = new int[A_SIZE];
        bmGs = new int[pattern.size];
        skip = new int[pattern.size];
        suff = new int[pattern.size];
    }

    catch (const std::bad_alloc& e) {
        printf("ERROR: No memory\n");
        exit(0);
    }

    tmpPos.row = 1;
    tmpPos.col = 1;

    QueueInit<char>(text, pattern.size);
    QueueInit<TPosition>(pos, pattern.size);

    PreBmGs(pattern.begin, pattern.size, bmGs, suff);
    PreBmBc(pattern.begin, pattern.size, bmBc, A_SIZE);
    memset(skip, 0, pattern.size * sizeof(int));

    bool isWordFound = false;

    while (true) {
        while (text.size < pattern.size && (ch = getchar()) != EOF) {
            if (ch == ' ' || ch == '\t') {
                if (isWordFound) {
                    QueuePush<char>(text, '{');

                    isWordFound = false;
                    ++tmpPos.col;
                }
            } else if (ch == '\n') {
                if (isWordFound) {
                    QueuePush<char>(text, '{');

                    isWordFound = false;
                }

                ++tmpPos.row;
                tmpPos.col = 1;
            } else {
                if (!isWordFound) {
                    QueuePush<TPosition>(pos, tmpPos);
                }

                QueuePush<char>(text, (char)tolower(ch));

                isWordFound = true;
            }
        }

        if (text.size < pattern.size) {
            break;
        }

        i = pattern.size - 1;

        while (i >= 0) {
            k = skip[i];
            s = suff[i];

            if (k > 0) {
                if (k > s) {
                    if (i + 1 == s) {
                        i = -1;
                    } else {
                        i -= s;
                    }

                    break;
                } else {
                    i -= k;

                    if (k < s) {
                        break;
                    }
                }
            } else {
                if (pattern.begin[i] == text.begin[(i + text.offset) % pattern.size]) {
                    --i;
                } else {
                    break;
                }
            }
        }

        if (i < 0) {
            TPosition wp = pos.begin[pos.offset];

            printf("%d, %d\n", wp.row, wp.col);

            skip[pattern.size - 1] = pattern.size;
            shift = bmGs[0];
        } else {
            int ind = text.begin[(i + text.offset) % pattern.size] - 'a';

            skip[pattern.size - 1] = pattern.size - 1 - i;
            shift = Max(bmGs[i], bmBc[ind] - pattern.size + 1 + i);
        }

        int offset = text.offset;

        for (size_t z = 0; z < shift; ++z) {
            QueuePop<char>(text);

            if (text.begin[(offset + z) % pattern.size] == '{') {
                QueuePop<TPosition>(pos);
            }
        }

        memcpy(skip, skip + shift, (pattern.size - shift) * sizeof(int));
        memset(skip + pattern.size - shift, 0, shift * sizeof(int));
    }

    QueueDestroy<char>(text);
    QueueDestroy<TPosition>(pos);

    delete[] bmBc;
    delete[] bmGs;
    delete[] skip;
    delete[] suff;
}