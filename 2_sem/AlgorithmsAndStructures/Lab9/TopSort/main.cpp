#include <iostream>
#include <vector>
#include <stack>

struct Node {
    enum Color {
        white = 0, gray, black
    };

    std::vector<size_t> connected;
    Color color = white;
};

std::stack<size_t> path;

void visit(std::vector<Node> &graph, size_t &index) {
    graph[index].color = Node::gray;

    for (auto &i : graph[index].connected) {
        if (graph[i].color == Node::white) {
            visit(graph, i);
        } else if (graph[i].color == Node::gray) {
            std::cout << "-1";
            exit(0);
        }
    }

    graph[index].color = Node::black;
    path.push(index);
}

void dfs(std::vector<Node> &graph) {
    for (auto &n : graph) {
        n.color = Node::white;
    }


    for (size_t i = 0; i < graph.size(); i++) {
        if (graph[i].color == Node::white) {
            visit(graph, i);
        }
    }
};

int main() {
    std::freopen("topsort.in", "r", stdin);
    std::freopen("topsort.out", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Node> graph(n);

    for (size_t i = 0; i < m; ++i) {
        size_t x, y;
        std::cin >> x >> y;
        --x; --y;

        graph[x].connected.push_back(y);
    }

    dfs(graph);

    if (path.empty()) {
        std::cout << "-1";
    } else {
        while (!path.empty()) {
            std::cout << path.top() + 1 << ' ';
            path.pop();
        }
    }

    return 0;
}
