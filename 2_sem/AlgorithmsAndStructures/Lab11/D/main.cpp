#include <iostream>
#include <vector>
#include <set>
#include <limits>

struct Edge {
    size_t from;
    size_t to;

    int64_t weight;

    Edge(size_t f, size_t t, int64_t w)
            : from(f), to(t), weight(w) {};
};

const int64_t INF = 8e18;

void dfs(std::vector<std::vector<int64_t>> &graph, std::vector<bool> &indicator, size_t i) {
    indicator[i] = true;

    for (auto &j : graph[i]) {
        if (!indicator[j])
            dfs(graph, indicator, j);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("path.in", "r", stdin);
    std::freopen("path.out", "w", stdout);


    size_t n, m, s;
    std::cin >> n >> m >> s;
    --s;

    std::vector<Edge> edges;
    std::vector<std::vector<int64_t >> graph(n);
    std::vector<std::vector<int64_t>> weights(n, std::vector<int64_t>(n, INF));

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        int64_t c;
        std::cin >> a >> b >> c;

        edges.emplace_back(a - 1, b - 1, c);
        weights[a - 1][b - 1] = c;
        graph[a - 1].push_back(b - 1);
    }

    std::vector<int64_t> distances(n, INF);
    std::vector<int64_t> parents(n, -1);
    std::vector<bool> nonExists(n, false);
    distances[s] = 0;

    std::vector<size_t> l;

    for (size_t _ = 0; _ < n; ++_) {
        l.resize(0);

        for (auto &edge : edges) {
            if (distances[edge.from] < INF) {
                if (distances[edge.to] > distances[edge.from] + edge.weight) {
                    distances[edge.to] = std::max(-INF, distances[edge.from] + edge.weight);
                    parents[edge.to] = edge.from;
                    l.push_back(edge.to);
                }
            }
        }
    }

    for (auto &v : l) {
        dfs(graph, nonExists, v);
    }


    for (size_t i = 0; i < n; ++i) {
        if (nonExists[i]) {
            std::cout << "-\n";
        } else if (distances[i] == INF) {
            std::cout << "*\n";
        } else {
            std::cout << distances[i] << '\n';
        }
    }


    return 0;
}