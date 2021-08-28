#include <iostream>
#include <vector>

std::vector<int> buildPrefix(const std::string &string) {
    std::vector<int> prefix(string.size());
    int j = 0, i = 1;

    while (i < string.size()) {
        if (string[j] == string[i]) {
            prefix[i] = j + 1;
            ++j;
            ++i;
        } else {
            if (j > 0) {
                j = prefix[j - 1];
            } else {
                prefix[i] = 0;
                ++i;
            }
        }
    }

    return prefix;
}

std::vector<int> SubstringEntries(const std::string &, const std::string &);

std::vector<int> Prefixes(const std::string &);

std::vector<std::vector<int>> EndingMachine(int, const std::string &);

std::vector<std::string> StringsPresence(const std::string &, const std::vector<std::string> &);

std::vector<bool> DoesEnters(const std::string &, const std::vector<std::string> &);

template<typename T>
void printVector(const std::vector<T> &v, bool withSize = false, bool isCovariant = false) {
    if (withSize)
        std::cout << v.size() << '\n';
    for (const T &i : v)
        std::cout << i << (isCovariant ? '\n' : ' ');
}

template<typename T>
void printMatrix(const std::vector<std::vector<T>> &m) {
    for (const auto &i : m) {
        printVector(i);
        std::cout << '\n';
    }
}

int main() {
#ifndef __APPLE__
    std::freopen("search4.in", "r", stdin);
    std::freopen("search4.out", "w", stdout);
#endif

    int n;
    std::cin >> n;

//    std::vector<std::string> strings(n);
//    for (int i = 0; i < n; std::cin >> strings[i], ++i);

    std::string string;
    std::cin >> string;

//    std::string substring;
//    std::cin >> substring;
//
//    printVector(SubstringEntries(string, substring), true);
//    printVector(Prefixes(string));
    printMatrix(EndingMachine(n, string));

//    auto res = DoesEnters(string, strings);
//
//    for (const auto &a : res)
//        std::cout << (a ? "YES" : "NO") << '\n';

    return 0;
}

std::vector<int>
SubstringEntries(const std::string &string, const std::string &substring) {
    int i = 0, j = 0;
    std::vector<int> prefix = buildPrefix(substring);
    std::vector<int> entries;

    while (i < string.size()) {
        if (string[i] == substring[j]) {
            ++i;
            ++j;
        } else {
            if (j > 0) {
                j = prefix[j - 1];
            } else {
                ++i;
            }
        }

        if (j == substring.size()) {
            entries.push_back(i - (int) substring.size());
            j = prefix[j - 1];
        }
    }

    return entries;
}

std::vector<int>
Prefixes(const std::string &string) {
    std::vector<int> prefix = buildPrefix(string);

    for (const int &count : prefix) {
        std::cout << count << ' ';
    }

    return prefix;
}

std::vector<std::vector<int>>
EndingMachine(int power, const std::string &s) {
    std::string string = s + (char) -1;
    std::vector<int> prefix = buildPrefix(string);
    std::vector<std::vector<int>> machine(string.size(), std::vector<int>(power));

    for (int i = 0; i < string.size(); ++i) {
        for (char c = 0; (int) c < power; ++c) {
            if (i > 0 && c + 'a' != string[i]) {
                machine[i][c] = machine[prefix[i - 1]][c];
            } else if (c + 'a' == string[i]) {
                machine[i][c] = i + 1;
            } else {
                machine[i][c] = i;
                std::cout << i << '\n';
            }
        }
    }

    return machine;
}

std::vector<bool> DoesEnters(const std::string &string, const std::vector<std::string> &prototypes) {
    std::vector<std::vector<std::vector<int>>> machines(prototypes.size());
    for (int i = 0; i < prototypes.size(); ++i)
        machines[i] = EndingMachine('z' - 'a' + 1, prototypes[i]);

    std::vector<bool> result(prototypes.size());

    for (int i = 0; i < machines.size(); ++i) {
        int q = 0;

//        printMatrix(machines[i]);
//        std::cout << '\n';

        for (const char &c : string) {
            q = machines[i][q][c - 'a'];
            if (q == prototypes[i].size()) {
                result[i] = true;
                break;
            }
        }
    }

    return result;
}