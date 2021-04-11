#include <iostream>
#include <vector>

const int64_t mod = 1e9;

std::vector<size_t> sequence;
std::vector<std::vector<int64_t >> counts;


int64_t count(size_t i, size_t j) {
    if (i > j)
        return 0;

    if (counts[i][j] != -1)
        return counts[i][j];

    if (sequence[i] != sequence[j])
        counts[i][j] = (count(i, j - 1) + count(i + 1, j) - count(i + 1, j - 1)) % mod;
    else
        counts[i][j] = (count(i, j - 1) + count(i + 1, j) + 1) % mod;

    if (counts[i][j] < 0)
        counts[i][j] += mod;

    return counts[i][j];
}

int main() {
    
    size_t n;
    std::cin >> n;

    sequence.resize(n);
    counts.resize(n, std::vector<int64_t>(n, -1));

    for (size_t i = 0; i < n; std::cin >> sequence[i], ++i);
    for (size_t i = 0; i < n; counts[i][i] = 1, ++i);

    std::cout << count(0, n - 1) % mod;

    return 0;
}