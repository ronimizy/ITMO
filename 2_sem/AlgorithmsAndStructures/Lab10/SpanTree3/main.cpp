#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using weight = unsigned long long;
using pair = std::pair<weight, size_t>;

int main() {
    std::freopen("spantree3.in", "r", stdin);
    std::freopen("spantree3.out", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<pair> > graph(n);

    size_t a, b, c;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> a >> b >> c;
        --a;
        --b;

        graph[a].push_back(std::make_pair(b, c));
        graph[b].push_back(std::make_pair(a, c));
    }

    std::priority_queue<pair, std::vector<pair>, std::greater<> > queue;
    std::vector<bool> removed(n, false);
    std::vector<weight> keys(n, std::numeric_limits<weight>::max());

    keys[0] = 0;
    queue.push(std::make_pair(0, 0));

    while (!queue.empty()) {
        size_t i = queue.top().second;
        removed[i] = true;
        queue.pop();

        std::vector<pair>::iterator it;
        for (it = graph[i].begin(); it != graph[i].end(); ++it) {
            size_t j = it->first;
            weight w = it->second;

            if (!removed[j] && w < keys[j]) {
                keys[j] = w;
                queue.push(std::make_pair(w, j));
            }
        }
    }

    weight sum = 0;
    for (auto &it : keys) {
        sum += it;
    }

    std::cout << sum;

    return 0;
}