#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<bool>> &graph, std::vector<std::vector<long>> &dynamic, size_t index) {
    dynamic[index][0] = 0;
    dynamic[index][1] = 1;

    for (size_t i = 0; i < graph.size(); ++i) {
        if (graph[index][i])
            dfs(graph, dynamic, i);
    }

    for (size_t i = 0; i < graph.size(); ++i) {
        if (graph[index][i]) {
            dynamic[index][1] += dynamic[i][0];
            dynamic[index][0] += std::max(dynamic[i][0], dynamic[i][1]);
        }
    }
}


int main() {
    size_t n;
    std::cin >> n;

    std::vector<std::vector<bool>> graph(n, std::vector<bool>(n));
    size_t root;

    for (size_t i = 0; i < n; ++i) {
        size_t parent;
        std::cin >> parent;

        if (parent == 0)
            root = i;
        else {
//            graph[i][parent - 1] = true;
            graph[parent - 1][i] = true;
        }
    }

    std::vector<std::vector<long>> dynamic(n, std::vector<long>(2));

    dfs(graph, dynamic, root);

    std::cout << std::max(dynamic[root][0], dynamic[root][1]);

    return 0;
}
