#include <iostream>
#include <vector>

bool validMove(long n, long m, std::pair<int, int> move) {
    if (move.first < 0 || move.second < 0)
        return false;

    if (move.first >= n || move.second >= m)
        return false;

    return true;
}

long
dfs(std::vector<std::vector<long>> &field, std::pair<long, long> position, const std::pair<long, long> &destination) {
    if (field[position.first][position.second] != 0)
        return field[position.first][position.second];

    if (position == destination)
        return 1;

    if (validMove(field.size(), field[0].size(), {position.first + 2, position.second - 1}))
        field[position.first][position.second] += dfs(field, {position.first + 2, position.second - 1}, destination);

    if (validMove(field.size(), field[0].size(), {position.first + 2, position.second + 1}))
        field[position.first][position.second] += dfs(field, {position.first + 2, position.second + 1}, destination);

    if (validMove(field.size(), field[0].size(), {position.first + 1, position.second + 2}))
        field[position.first][position.second] += dfs(field, {position.first + 1, position.second + 2}, destination);

    if (validMove(field.size(), field[0].size(), {position.first - 1, position.second + 2}))
        field[position.first][position.second] += dfs(field, {position.first - 1, position.second + 2}, destination);

    return field[position.first][position.second];
}

int main() {
    std::freopen("knight2.in", "r", stdin);
#ifndef __APPLE__
    std::freopen("knight2.out", "w", stdout);
#endif

    long n, m;
    std::cin >> n >> m;

    std::vector<std::vector<long>> field(n, std::vector<long>(m, 0));

    std::cout << dfs(field, {0, 0}, {n - 1, m - 1});

    return 0;
}
