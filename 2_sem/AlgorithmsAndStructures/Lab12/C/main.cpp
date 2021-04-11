#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    std::string a;
    std::string b;
    std::cin >> a >> b;

    std::vector<std::vector<size_t> > sizes(a.size() + 1,
                                            std::vector<size_t>(b.size() + 1));

    //Python++
    for (size_t i = 1; i <= a.size(); ++i)
        for (size_t j = 1; j <= b.size(); ++j)
            if (a[i - 1] == b[j - 1])
                sizes[i][j] = sizes[i - 1][j - 1] + 1;
            else
                sizes[i][j] = std::max(sizes[i - 1][j], sizes[i][j - 1]);

    size_t i = a.size(), j = b.size();
    size_t length = sizes[i][j];
    char substring[length + 1];
    substring[length] = '\0';

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            substring[--length] = a[i - 1];
            --i;
            --j;
        } else {
            if (sizes[i - 1][j] > sizes[i][j - 1])
                --i;
            else
                --j;
        }
    }

    std::reverse(&substring[0], &substring[sizes[a.size()][b.size()]]);
    std::cout << substring;

    return 0;
}