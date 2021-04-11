#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

struct Node {
    enum Color {
        white = 0, black
    };
    std::vector<size_t> connected;
    Color color = white;

    size_t component = 0;
};

std::vector<size_t> sorted;
size_t currentComponent = 1;

void topSort(std::vector<Node> &graph, size_t index) {
    graph[index].color = Node::black;

    for (size_t &i : graph[index].connected) {
        if (graph[i].color == Node::white) {
            topSort(graph, i);
        }
    }

    sorted.push_back(index);
}

void dfs(std::vector<Node> &graph, size_t &index) {
    graph[index].component = currentComponent;

    for (size_t &i : graph[index].connected) {
        if (graph[i].component == 0) {
            dfs(graph, i);
        }
    }
}


int main() {
    std::freopen("cond.in", "r", stdin);
    std::freopen("cond.out", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Node> graph(n);
    std::vector<Node> transposed(n);

    for (size_t i = 0; i < m; ++i) {
        size_t x, y;
        std::cin >> x >> y;
        --x; --y;

        graph[x].connected.push_back(y);
        transposed[y].connected.push_back(x);
    }

    for (size_t i = 0; i < n; ++i) {
        if (graph[i].color == Node::white) {
            topSort(graph, i);
        }
    }
    std::reverse(sorted.begin(), sorted.end());

    for (size_t &i : sorted) {
        if (transposed[i].component == 0) {
            dfs(transposed, i);
            ++currentComponent;
        }
    }

    std::cout << currentComponent - 1 << '\n';
    for (auto &node : transposed) {
        std::cout << node.component << ' ';
    }

    return 0;
}
