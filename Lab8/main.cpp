#include <iostream>
#include <vector>
#include <algorithm>

struct ARRAYS {
    int start;
    int end;
};

ARRAYS FindMaxEnd(int start, int time, ARRAYS arr[], int size)
{
    ARRAYS tmp = arr[0];
    ARRAYS max = arr[0];

    while (start <= time) {
        for (int i = 0; i < size; ++i) {
            if (arr[i].start == start && arr[i].end > tmp.end)
                tmp = arr[i];
        }

        if (max.end < tmp.end) {
            max = tmp;
        }
        ++start;
    }
    return max;
}

void quickSortEnd(ARRAYS arr[], int left, int right) {
    int i = left, j = right;
    ARRAYS tmp {0,0};
    int pivot = arr[(left + right) / 2].end;

    /* partition */
    while (i <= j) {
        while (arr[i].end < pivot)
            i++;
        while (arr[j].end > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSortEnd(arr, left, j);
    if (i < right)
        quickSortEnd(arr, i, right);

}

int main()
{
    std::vector<ARRAYS> res;
    ARRAYS pair {0,0};
    int N = 0;
    int M = 0;
    std::cin >> N;
    ARRAYS mass[255];
    ARRAYS out[255];
    for (int i = 0; i < N; ++i) {
        std::cin >> pair.start;
        std::cin >> pair.end;
        mass[i] = pair;
        out[i] = pair;
    }
    std::cin >> M;

    quickSortEnd(mass, 0, N - 1);

    res.push_back(mass[0]);
    int time = mass[0].end;
    int i = 1;
    while (i < N) {
        if (mass[i].start <= time) {
            ARRAYS tmp = FindMaxEnd(mass[i].start, time, mass, N);
            if (tmp.end != res[res.size() - 1].end) {
                res.push_back(tmp);
                time = tmp.end;
            }
            if (res[0].end <= 0) {
                res.erase(res.begin() + 0);
                std::vector<ARRAYS>(res).swap(res);
            }
            if (res[0].start >= tmp.start && res[res.size() - 1].end <= tmp.end) {
                while (!res.empty()) {
                    res.pop_back();
                }
                res.push_back(tmp);
            }
        }
        ++i;
        if (time >= M) break;
    }

    if (res.empty() || res[0].start > 0 || res[res.size() - 1].end < M) {
        std::cout << "0\n";
    } else {
        std::cout<< res.size() << "\n";
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < res.size(); ++k) {
                if (out[j].start == res[k].start && out[j].end == res[k].end) {
                    std::cout << res[k].start << " " << res[k].end << "\n";
                }
            }
        }
    }
    return 0;
}