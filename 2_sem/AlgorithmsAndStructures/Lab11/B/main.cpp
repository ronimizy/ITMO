#include <iostream>
#include <vector>

using Weight = long long;
using Row = std::vector<Weight>;
using Graph = std::vector<Row>;

const Weight SUP = 1e5;

void georgeFloyd(Graph &graph) {
    Graph prev;
    size_t n = graph.size();

    for (size_t k = 0; k < n; ++k) {
        prev = Graph(graph);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                graph[i][j] = std::min(prev[i][j], prev[i][k] + prev[k][j]);
            }
        }
    }

    for (size_t i = 0; i < n; ++i)
        graph[i][i] = 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("pathsg.in", "r", stdin);
    std::freopen("pathsg.out", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;

    Graph graph(n, Row(n, SUP));

    for (size_t i = 0; i < m; ++i) {
        size_t a, b, c;
        std::cin >> a >> b >> c;

        graph[a - 1][b - 1] = c;
    }

    georgeFloyd(graph);

    for (auto &i : graph) {
        for (auto &j : i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}