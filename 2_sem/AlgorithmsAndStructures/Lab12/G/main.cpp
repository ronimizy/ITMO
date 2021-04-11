#include <iostream>
#include <vector>


int main() {
    std::freopen("knapsack.in", "r", stdin);
#ifndef __APPLE__
    std::freopen("knapsack.out", "w", stdout);
#endif
    size_t max, n;
    std::cin >> max >> n;

    std::vector<int> ingots(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ingots[i];

    //weights[i][i] - max weight that we can get by taking from first 'i' ingots with weight less than 'j'
    std::vector<std::vector<int>> weights(n, std::vector<int>(max + 1));
    for (size_t j = 0; j < max + 1; ++j) {
        weights[0][j] = ingots[0] > j ? 0 : ingots[0];
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < max + 1; ++j) {
            if (ingots[i] > j)
                weights[i][j] = weights[i - 1][j];
            else
                weights[i][j] = std::max(weights[i - 1][j], weights[i - 1][j - ingots[i]] + ingots[i]);
        }
    }

    std::cout << weights[n - 1][max];

    return 0;
}
