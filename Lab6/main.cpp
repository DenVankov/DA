#include <iostream>
#include "TBigInt.h"

int main() {
    std::string Numb1str, Numb2str;
    char operation;
    while (std::cin >> Numb1str >> Numb2str >> operation) {
        TBigInt numb1(Numb1str);
        TBigInt numb2(Numb2str);
        switch (operation) {
            case '<': {
                numb1 < numb2 ? std::cout << "true\n" : std::cout << "false\n";
                break;
            }

            case '>': {
                numb1 > numb2 ? std::cout << "true\n" : std::cout << "false\n";
                break;
            }

            case '=': {
                numb1 == numb2 ? std::cout << "true\n" : std::cout << "false\n";
                break;
            }

            case '+': {
                std::cout << numb1 + numb2 << "\n";
                break;
            }

            case '-': {
                if (numb1 < numb2)
                    std::cout << "Error\n";
                else
                    std::cout << numb1 - numb2 << "\n";
                break;
            }

            case '*': {
                std::cout << numb1 * numb2 << "\n";
                break;
            }

            case '/': {
                if (numb2 == TBigInt(0))
                    std::cout << "Error\n";
                else
                    std::cout << numb1 / numb2 << "\n";
                break;
            }

            case '^': {
                if (numb1 == TBigInt(0)) {
                    if (numb2 == TBigInt(0))
                        std::cout << "Error\n";
                    else
                        std::cout << "0\n";
                } else if (numb1 == TBigInt(1)) {
                    std::cout << "1\n";
                } else {
                    std::cout << numb1.Power(std::stoi(Numb2str)) << "\n";
                }
                break;
            }
        }
    }
    return 0;
}