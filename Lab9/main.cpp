#include <iostream>
#include <vector>
#include <algorithm>

const int64_t INF = 10000000000000;

struct edge {
    uint32_t from;
    uint32_t to;
    int64_t cost;
};

int64_t BellmanFord(std::vector<edge> &graph, uint32_t n, uint32_t start, uint32_t finish)
{
    std::vector<int64_t> d (n, INF);

    d[start] = 0;
    for (;;) {
        bool any = false;
        for (int j = 0; j < graph.size(); ++j)
            if (d[graph[j].from - 1] < INF)
                if (d[graph[j].to - 1] > d[graph[j].from - 1] + graph[j].cost) {
                    d[graph[j].to - 1] = d[graph[j].from - 1] + graph[j].cost;
                    any = true;
                }
        if (!any)  break;
    }
    return d[finish];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::vector<edge> graph;
    uint32_t n, m, start, finish = 0;
    std::cin >> n >> m >> start >> finish;
    graph.resize(m);

    for (int i = 0; i < m; ++i) {
        std::cin >> graph[i].from >> graph[i].to >> graph[i].cost;
    }

    int64_t ans = BellmanFord(graph, n, start - 1, finish - 1);
    if (ans == INF) {
        std::cout << "No solution\n";
    } else {
        std::cout << ans << "\n";
    }
    return 0;
}