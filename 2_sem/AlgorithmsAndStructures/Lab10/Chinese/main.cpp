#include <iostream>

#include <vector>
#include <stack>

#include <algorithm>
#include <limits>

using WeightType = long long;
using Edge = std::pair<WeightType, std::pair<size_t , size_t> >;
using Indicator = std::vector<bool>;
using Adj = std::vector<Indicator>;

#define INF std::numeric_limits<WeightType>::max()
#define mINF std::numeric_limits<WeightType>::min()

class Graph {
    size_t currentSize_;
    size_t root_;

    std::vector<Edge> edges_;

    static Adj
    makeMatrix(size_t size, std::vector<Edge> &edges, bool transposed = false) {
        Adj matrix(size, Indicator(size));

        for (auto &edge : edges) {
            matrix
            [transposed ? edge.second.second : edge.second.first]
            [transposed ? edge.second.first : edge.second.second] = true;
        }

        return matrix;
    }

    static void
    dfsIR(Adj &matrix, size_t i, std::vector<bool> &visited) {
        visited[i] = true;

        for (size_t j = 0; j < matrix.size(); ++j) {
            if (matrix[i][j] && !visited[j]) {
                dfsIR(matrix, j, visited);
            }
        }
    }

    [[nodiscard]] bool
    isReachable(size_t from, std::vector<Edge> &edges) const {
        Adj matrix = makeMatrix(currentSize_, edges);
        Indicator visited(currentSize_);

        dfsIR(matrix, from, visited);

        return std::all_of(visited.begin(), visited.end(), [](bool a) { return a; });
    }

    static void
    topSort(Adj &matrix, size_t i, Indicator &visited, std::stack<size_t> &sorted) {
        visited[i] = true;

        for (size_t j = 0; j < matrix.size(); ++j) {
            if (matrix[i][j] && !visited[j]) {
                topSort(matrix, j, visited, sorted);
            }
        }

        sorted.push(i);
    }

    static void
    dfsC(Adj &matrix, size_t i, Indicator &visited, std::vector<size_t> &components, size_t &currentComponent) {
        visited[i] = true;
        components[i] = currentComponent;

        for (size_t j = 0; j < matrix.size(); ++j) {
            if (matrix[i][j] && !visited[j]) {
                dfsC(matrix, j, visited, components, currentComponent);
            }
        }
    }

    std::vector<size_t>
    condensate(std::vector<Edge> &edges) {
        Adj matrixOriginal = makeMatrix(currentSize_, edges, false);
        Adj matrixTransposed = makeMatrix(currentSize_, edges, true);

        std::vector<size_t> components(currentSize_);
        Indicator visited(currentSize_);
        size_t currentComponent = 0;
        std::stack<size_t> sorted;

        for (size_t i = 0; i < currentSize_; ++i) {
            if (!visited[i]) {
                topSort(matrixOriginal, i, visited, sorted);
            }
        }
        visited.assign(currentSize_, false);

        while (!sorted.empty()) {
            size_t i = sorted.top();
            sorted.pop();

            if (!visited[i]) {
                dfsC(matrixTransposed, i, visited, components, currentComponent);
                ++currentComponent;
            }
        }

        root_ = components[root_];
        currentSize_ = currentComponent;

        return components;
    }

public:
    Graph(size_t root, size_t size) : root_(root), currentSize_(size) {};

    void
    addEdge(size_t from, size_t to, WeightType weight) { edges_.push_back({weight, {from, to}}); }

    bool
    hasMST() { return isReachable(root_, edges_); }

    [[nodiscard]] WeightType
    mstSize() {
        WeightType result = 0;
        std::vector<Edge> viewedEdges(edges_);

        while (true) {
            std::vector<WeightType> minimalWeights(currentSize_, INF);
            std::vector<Edge> zeroEdges;
            minimalWeights[root_] = mINF;

            for (const auto &edge : viewedEdges) {
                minimalWeights[edge.second.second] = std::min(minimalWeights[edge.second.second], edge.first);
            }
            for (size_t i = 0; i < currentSize_; ++i) {
                if (i != root_) {
                    result += minimalWeights[i];
                }
            }
            for (auto &edge : viewedEdges) {
                if (minimalWeights[edge.second.second] == edge.first) {
                    zeroEdges.push_back({0, {edge.second.first, edge.second.second}});
                }

                edge.first -= minimalWeights[edge.second.second];
            }

            if (isReachable(root_, zeroEdges))
                break;

            std::vector<size_t> components = condensate(zeroEdges);
            std::vector<Edge> buffer(viewedEdges);
            viewedEdges.resize(0);

            for (const auto &edge : buffer) {
                if (components[edge.second.first] != components[edge.second.second]) {
                    viewedEdges.push_back({edge.first,
                                           {components[edge.second.first],
                                            components[edge.second.second]}});
                }
            }
        }

        return result;
    }
};


void solve() {
    size_t n, m;
    std::cin >> n >> m;

    Graph graph(0, n);

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        WeightType c;

        std::cin >> a >> b >> c;

        graph.addEdge(a - 1, b - 1, c);
    }

    if (graph.hasMST()) {
        std::cout << "YES\n" << graph.mstSize() << '\n';
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("chinese.in", "r", stdin);
    std::freopen("chinese.out", "w", stdout);

#ifdef __APPLE__
    for (size_t i = 0; i < 1; ++i) {
        clock_t start = clock();
        solve();
        clock_t end = clock();
        std::clog << end - start << " / " << CLOCKS_PER_SEC << '\n';
    }
#else
    solve();
#endif
    return 0;
}