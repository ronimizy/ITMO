#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <stack>

struct Edge {
    size_t from;
    size_t to;

    int64_t weight;

    Edge(size_t f, size_t t, int64_t w)
            : from(f), to(t), weight(w) {};
};

const int64_t INF = 1e13;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("negcycle.in", "r", stdin);
    std::freopen("negcycle.out", "w", stdout);


    size_t n;
    std::cin >> n;

    std::vector<Edge> edges;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            int64_t weight;
            std::cin >> weight;

            if (weight != 1e9) {
                edges.emplace_back(i, j, weight);
            }
        }
    }

    std::vector<int64_t> distances(n);
    std::vector<int64_t> parents(n, -1);

    int64_t last;

    for (size_t i = 0; i < n; ++i) {
        last = -1;

        for (auto &edge : edges) {
            if (distances[edge.to] > distances[edge.from] + edge.weight) {
                distances[edge.to] = std::max(-INF, distances[edge.from] + edge.weight);
                parents[edge.to] = edge.from;
                last = edge.to;
            }
        }
    }

    if (last == -1)
        std::cout << "NO";
    else {
        int64_t v = last;

        for (size_t _ = 0; _ < n; ++_)
            v = parents[v];

        std::stack<int64_t> path;

        for (int64_t current = v; !(current == v && path.size() > 1); current = parents[current])
            path.push(current);

        path.push(v);

        std::cout << "YES\n" << path.size() << '\n';

        while (!path.empty()) {
            std::cout << path.top() + 1 << ' ';
            path.pop();
        }
    }


    return 0;
}