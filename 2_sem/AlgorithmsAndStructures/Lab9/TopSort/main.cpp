#include <iostream>
#include <vector>
#include <queue>

struct Node {
    enum Color {
        white = 0, gray, black
    };

    std::vector<size_t> connected;
    Color color = white;
};

std::queue<size_t> path;

void visit(std::vector<Node> &graph, size_t &index) {
    graph[index].color = Node::gray;

    for (size_t i = 0; i < graph[index].connected.size(); ++i) {
        if (graph[i].color == Node::white) {
            visit(graph, i);
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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
