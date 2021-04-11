#include <iostream>
#include <vector>

struct Node {
    enum Color {
        white = 0, red, blue
    };

    std::vector<size_t> connected;
    Color color = white;
};

Node::Color flipped(Node &node) {
    return node.color == Node::red ? Node::blue : Node::red;
}

void dfs(std::vector<Node> &graph, size_t &index) {
    for (size_t &i : graph[index].connected) {
        if (graph[i].color == Node::white) {
            graph[i].color = flipped(graph[index]);
            dfs(graph, i);
        } else if (graph[i].color == graph[index].color) {
            std::cout << "NO";
            exit(0);
        }
    }
}


int main() {
    std::freopen("bipartite.in", "r", stdin);
    std::freopen("bipartite.out", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Node> graph(n);

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        --a; --b;

        graph[a].connected.push_back(b);
        graph[b].connected.push_back(a);
    }

    for (size_t i = 0; i < n; ++i) {
        if (graph[i].color == Node::white) {
            graph[i].color = Node::red;
            dfs(graph, i);
        }
    }

    std::cout << "YES";

    return 0;
}
