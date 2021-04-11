#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using Sequence = std::vector<int>;

int main() {
    size_t n;
    std::cin >> n;

    Sequence sequence(n);
    Sequence map(n);
    Sequence parents(n, -1);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> sequence[i];
        map[i] = 1;

        for (int j = 0; j < i; ++j) {
            if (sequence[j] < sequence[i]) {
                if (map[i] < map[j] + 1) {
                    map[i] = map[j] + 1;
                    parents[i] = j;
                }
            }
        }
    }

    long index = std::max_element(map.begin(), map.end()) - map.begin();
    std::stack<long> stack;

    for (long i = index; i != -1; i = parents[i])
        stack.push(sequence[i]);

    std::cout << stack.size() << '\n';
    for (; !stack.empty(); stack.pop())
        std::cout << stack.top() << ' ';


    return 0;
}
