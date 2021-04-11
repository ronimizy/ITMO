#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<size_t >>;
using List = std::vector<std::pair<size_t, size_t>>;

Graph additionalGraph(const Graph &graph);

std::ostream &operator<<(std::ostream &out, const Graph &graph);

std::ostream &operator<<(std::ostream &out, const List &list);

Graph listToGraph(const List &list, size_t size);

List graphToList(const Graph &graph);




int main() {
    std::freopen("graph.in", "r", stdin);

    size_t n, m;
    std::cin >> n >> m;

    List list;

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        std::cin >> a >> b;

        list.emplace_back(a, b);
    }


    std::cout << additionalGraph(listToGraph(list, n));


    return 0;
}


Graph
additionalGraph(const Graph &graph) {
    Graph additional(graph.size(), std::vector<size_t>(graph.size(), 0));

    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = i + 1; j < graph.size(); ++j) {
            if (graph[i][j] == 0) {
                additional[i][j] = 1;
                additional[j][i] = 1;
            }
        }
    }

    return additional;
}

std::ostream &
operator<<(std::ostream &out, const Graph &graph) {
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = 0; j < graph.size(); ++j) {
            out << graph[i][j] << ", ";
        }

        out << '\n';
    }

    return out;
}

std::ostream &
operator<<(std::ostream &out, const List &list) {
    for (const auto &pair : list) {
        out << pair.first << ' ' << pair.second << '\n';
    }

    return out;
}

Graph
listToGraph(const List &list, size_t size) {
    Graph graph(size, std::vector<size_t>(size));

    for (const auto &pair : list) {
        graph[pair.first][pair.second] = 1;
        graph[pair.second][pair.first] = 1;
    }

    return graph;
}

List
graphToList(const Graph &graph) {
    List list;

    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = i; j < graph.size(); ++j) {
            if (graph[i][j] != 0) {
                list.emplace_back(i, j);
            }
        }
    }

    return list;
}