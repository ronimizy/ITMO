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
};


std::stack<size_t> path;
size_t n, m;

void dfs(std::vector<Node> &graph, size_t &index, size_t depth) {
    graph[index].color = Node::black;

    for (size_t &i : graph[index].connected) {
        if (graph[i].color == Node::white) {
            dfs(graph, i, depth + 1);
        }
    }

    path.push(index);
}

int main() {
    std::freopen("hamiltonian.in", "r", stdin);
    std::freopen("hamiltonian.out", "w", stdout);

    std::cin >> n >> m;

    std::vector<Node> graph(n);

    for (size_t i = 0; i < m; ++i) {
        size_t x, y;
        std::cin >> x >> y;
        --x; --y;

        graph[x].connected.push_back(y);
    }

    for (size_t i = 0; i < n; ++i) {
        if (graph[i].color == Node::white) {
            dfs(graph, i, 1);
        }
    }

    bool isHamiltonian = false;
    size_t parent, viewed;

    if (!path.empty()) {
        parent = path.top();
        path.pop();

        isHamiltonian = true;
    }

    while (isHamiltonian && !path.empty()) {
        viewed = path.top();
        path.pop();

        if (std::any_of(graph[parent].connected.begin(), graph[parent].connected.end(), [&](size_t a) {return a == viewed; })) {
            isHamiltonian = true;
        } else {
            isHamiltonian = false;
        }

        parent = viewed;
    }

    std::cout << (isHamiltonian ? "YES" : "NO");

    return 0;
}
