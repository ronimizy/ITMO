#include <iostream>
#include <vector>

struct Node {
    enum Color {
        white = 0, black
    };

    std::vector <size_t> connected;
    std::vector<Color> color;

    void connect(size_t y) {
        connected.push_back(y);
        color.push_back(white);
    }
};

bool dfs(std::vector <Node> &graph, size_t index, bool turn) {
    for (size_t i = 0; i < graph[index].connected.size(); ++i) {
        if (graph[index].color[i] == Node::white) {
            graph[index].color[i] = Node::black;
            if (dfs(graph, graph[index].connected[i], !turn) == turn) {
                return turn;
            }
        }
    }

    return !turn;
}

int main() {
    std::freopen("game.in", "r", stdin);
    std::freopen("game.out", "w", stdout);

    size_t n, m, start;
    std::cin >> n >> m >> start;

    std::vector <Node> graph(n);

    size_t x, y;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> x >> y;
        graph[x - 1].connect(y - 1);
    }

    std::cout << (!dfs(graph, start - 1, false) ? "First player wins" : "Second player wins");

    return 0;
}
