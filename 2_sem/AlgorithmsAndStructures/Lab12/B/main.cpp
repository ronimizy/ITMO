#include <iostream>
#include <vector>
#include <stack>

using Sequence = std::vector<int64_t>;
using Stack = std::stack<int64_t>;

int main() {
    int64_t n;
    std::cin >> n;

    Sequence sequence(n);
    Sequence ends(n + 2, 1e10);
    Sequence indices(n + 2, -1);
    Sequence parents(n, -1);

    ends[0] = -1e10;

    for (size_t i = 0; i < n; std::cin >> sequence[i], ++i);

    for (size_t i = 0; i < n; ++i) {
        size_t left = -1, right = n;

        while (right - left > 1) {
            size_t mid = (left + right) / 2;

            if (ends[mid] < sequence[i])
                left = mid;
            else
                right = mid;
        }

        if (ends[right - 1] < sequence[i] && sequence[i] < ends[right]) {
            ends[right] = sequence[i];
            indices[right] = (int64_t) i;
            parents[i] = indices[right - 1];
        }
    }

    for (n = 0; ends[n + 1] < (int64_t) 1e10; ++n);

    Stack stack;
    for (int64_t index = indices[n], element = ends[n];
         index != -1;
         index = parents[index], stack.push(element), element = sequence[index]);

    std::cout << n << '\n';
    for (; !stack.empty(); std::cout << stack.top() << ' ', stack.pop());

    return 0;
}
