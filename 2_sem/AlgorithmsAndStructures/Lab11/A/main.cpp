#include <iostream>
#include <vector>
#include <set>
#include <limits>

using Arc = std::pair<int64_t , size_t >;

const int64_t SUP = std::numeric_limits<int64_t>::max();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("pathmgep.in", "r", stdin);
    std::freopen("pathmgep.out", "w", stdout);
    
    size_t n, s, f;
    std::cin >> n >> s >> f;
    --s;
    --f;
    
    std::vector<std::vector<Arc>> graph(n);
    
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            long long weight;
            std::cin >> weight;
            
            if (weight != -1 && weight != 0) {
                graph[i].emplace_back(weight, j);
                }
            }
        }
    
    
    std::vector<int64_t> distances(n, SUP);
    distances[s] = 0;
    
    
    std::set<std::pair<int64_t, size_t>> queue;
    queue.insert({0, s});
    
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
    
    if (distances[f] == SUP) {
        std::cout << -1;
        } else {
        std::cout << distances[f];
        }
    
    
    return 0;
}