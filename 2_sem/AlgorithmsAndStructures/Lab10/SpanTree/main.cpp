#include <iostream>
#include <vector>
#include <cmath>
#include <optional>
#include <algorithm>
#include <iomanip>

struct Node {
    double x = 0, y = 0;
    
    std::vector<double > connected;
    double &operator[](size_t i) { return connected[i]; }
    
    std::optional<double> minimumWeight;
    size_t parent = 0;
    
    explicit
    Node(size_t n) : connected(std::vector<double>(n)) {};
    
    double distance(const Node &n) const { return sqrt(pow(x - n.x, 2) + pow(y - n.y, 2)); }
    
    bool hasValue() const { return minimumWeight.has_value(); }
    
    double value() const { return minimumWeight.value(); }
};

int main() {
    std::freopen("spantree.in", "r", stdin);
    std::freopen("spantree.out", "w", stdout);

    size_t n;
    std::cin >> n;

    std::vector<Node> graph(n, Node(n));
    std::vector<size_t> indices(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> graph[i].x >> graph[i].y;
        indices[i] = i;

        for (size_t j = 0; j < i; ++j) {
            double distance = graph[i].distance(graph[j]);

            graph[i][j] = distance;
            graph[j][i] = distance;
        }
    }

    graph[0].minimumWeight = 0;

    std::vector<size_t > queue(indices);
    auto closure = [&graph] (const size_t &lhs, const size_t &rhs) {
        if (!graph[lhs].hasValue() && !graph[rhs].hasValue()) {
            return false;
        }
        if (graph[lhs].hasValue() && graph[rhs].hasValue()) {
            return graph[lhs].minimumWeight < graph[rhs].minimumWeight;
        }

        return graph[lhs].hasValue();
    };

    while (!queue.empty()) {
        std::sort(queue.begin(), queue.end(), closure);
        const size_t &i = queue.front();

        for (size_t &j : queue) {
            if (i != j && (!graph[j].hasValue() || graph[i][j] < graph[j].value())) {
                graph[j].parent = i;
                graph[j].minimumWeight = graph[i][j];
            }
        }

        queue.erase(queue.begin());
    }

    double sum = 0;
    for (const Node &node : graph) {
        sum += node.hasValue() ? node.value() : 0;
    }

    std::cout << std::fixed << std::setprecision(5) << sum;

    return 0;
}