#include <iostream>
#include <vector>
#include <stack>

uint32_t LENGTH, WIDTH;

void ReadRect(std::vector<std::vector<int>> &rectangle)
{
    rectangle.resize(LENGTH);
    for (int i = 0; i < LENGTH; ++i) {
        rectangle[i].resize(WIDTH);
            std::string string;
            std::cin >> string;
        for (int j = 0; j < WIDTH; ++j) {
            rectangle[i][j] = string[j] - '0';
        }
    }
}

int LineSquare(std::vector<int> &column)
{
    std::stack<int> stack;
    int tmpSquare = 0;
    int i = 0;
    while (i < WIDTH || !stack.empty()) {
        if (stack.empty() || (column[stack.top()] <= column[i] && i < WIDTH)) {
            stack.push(i);
            ++i;
        } else {
            int previous = stack.top();
            stack.pop();
            int current = column[previous] * (stack.empty() ? i : i - stack.top() - 1);
            if (current > tmpSquare) {
                tmpSquare = current;
            }
        }
    }
    return tmpSquare;
}

int main()
{
    std::cin >> LENGTH >> WIDTH;
    std::vector<std::vector<int>> rectangle;
    ReadRect(rectangle);
    int MaxSquare = 0;
    std::vector<int> Columns(WIDTH);
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (rectangle[i][j] == 0) {
                Columns[j]++;
            } else {
                Columns[j] = 0;
            }
        }
        int tmpSqr = LineSquare(Columns);
        if (tmpSqr > MaxSquare) {
            MaxSquare = tmpSqr;
        }
    }

    std::cout << MaxSquare << std::endl;
    return 0;
}