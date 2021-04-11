#include <iostream>
#include <vector>

int main() {
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<size_t > degrees(n);

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        std::cin >> a >> b;

        ++degrees[a - 1];
        ++degrees[b - 1];
    }

    for (auto &it : degrees) {
        std::cout << it << ' ';
    }

    return 0;
}
