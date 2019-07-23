#include <iostream>
#include <cstdio>
#include "BTree.h"

char LowerCase(char ch)
{
    return ch >= 'A' && ch <= 'Z' ? ch - 'A' + 'a' : ch;
}

bool IsLetter(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

void ReadLine(char *cmd, char *buff, TYPE *number) {
    char symb;
    size_t i = 0;
    symb = getchar();
    if (symb == EOF) {
        *cmd = 'Q';
        return;
    }

    if (symb == '+' || symb == '-') {
        getchar();
        *cmd = symb;

        while (true) {
            symb = LowerCase(getchar());
            if (!IsLetter(symb)) {
                break;
            }
            buff[i++] = symb;
        }

        buff[i] = '\0';
        if (*cmd == '+') {
            *number = 0;

            while ((symb = getchar()) != '\n') {
                *number = (*number) * 10 + symb - '0';
            }
        }
    } else if (symb == '!') {
        getchar();
        buff[0] = symb;

        while ((symb = getchar()) != ' ') {
            buff[i++] = symb;
        }

        buff[i] = '\0';
        i = 0;
        *cmd = buff[0];

        while ((symb = getchar()) != '\n') {
            buff[i++] = symb;
        }

        buff[i] = '\0';
    } else {
        *cmd = 'F';
        buff[0] = LowerCase(symb);
        i += 1;

        while ((symb = getchar()) != '\n') {
            buff[i++] = LowerCase(symb);
        }

        buff[i] = '\0';
    }
}

int main() {
    TBTree btree(3);

    while (true) {
        char cmd;
        char buff[255];
        TYPE number;

        ReadLine(&cmd, buff, &number);

        if (cmd == 'Q') {
            break;
        }

        switch(cmd) {
            case '+': {
                TBTree::TData data;
                data.key = buff;
                data.value = number;

                if (btree.Find(buff) == nullptr) {
                    btree.Insert(data);
                    printf("OK\n");
                } else {
                    printf("Exist\n");
                }
                break;
            }
            case '-': {
                if (btree.Find(buff) == nullptr) {
                    printf("NoSuchWord\n");
                } else {
                    btree.Remove(buff);
                    printf("OK\n");
                }
                break;
            }
            case 'L': {
                if (btree.Load(buff)) {
                    printf("OK\n");
                } else {
                    printf("ERROR: Couldn't load file\n");
                }
                break;
            }
            case 'S': {
                if (btree.Save(buff)) {
                    printf("OK\n");
                } else {
                    printf("ERROR: Couldn't create file\n");
                }
                break;
            }
            case 'F': {
                TBTree:: TData* data = btree.Find(buff);
                if (data == nullptr) {
                    printf("NoSuchWord\n");
                } else {
                    printf("OK: %llu\n", data->value);
                }
                break;
            }
       }
    }




    return 0;
}