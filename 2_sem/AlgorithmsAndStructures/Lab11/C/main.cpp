#include <iostream>
#include <vector>
#include <set>
#include <limits>

using Arc = std::pair<int64_t , size_t >;

const int64_t SUP = std::numeric_limits<int64_t>::max();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("pathbgep.in", "r", stdin);
    std::freopen("pathbgep.out", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<Arc>> graph(n);

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        int64_t c;
        std::cin >> a >> b >> c;

        graph[a - 1].emplace_back(c, b - 1);
        graph[b - 1].emplace_back(c, a - 1);
    }


    std::vector<int64_t> distances(n, SUP);
    distances[0] = 0;


    std::set<std::pair<int64_t, size_t>> queue;
    queue.insert({0, 0});

    while (!queue.empty()) {
        std::pair<int64_t, size_t> current = *queue.begin();
        queue.erase(queue.begin());

        for (auto &arc : graph[current.second]) {
            if (distances[arc.second] > current.first && distances[arc.second] > current.first + arc.first) {
                queue.erase({distances[arc.second], arc.second});
                queue.insert({current.first + arc.first, arc.second});
                distances[arc.second] = current.first + arc.first;
            }
        }
    }

    for (auto &d : distances) {
        std::cout << d << ' ';
    }


    return 0;
}