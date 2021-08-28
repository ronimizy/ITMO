#include <iostream>
#include <vector>
#include <cstring>

const int power = 26;

struct Node {
    int children[power];
    int moves[power];
    std::vector<int> numbers;
    
    bool isTerminating = false;
    bool isOut = false;
    char symbol;
    int parent;
    
    int suffixLink = -1;
    int goodSuffixLink = -1;
    
    Node(int p, char c) : parent(p), symbol(c) {
        memset(children, -1, power * sizeof(int));
        memset(moves, -1, power * sizeof(int));
        }
};

std::vector<Node> trie;
std::vector<bool> indicator;
int size = 0;

void addString(const std::string &);

int getMove(int, char);

int getSuffixLink(int);

int getGoodSuffixLink(int);

void check(int);

int main() {
#ifndef __APPLE__
    std::freopen("search4.in", "r", stdin);
std::freopen("search4.out", "w", stdout);
#endif
    
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    
    trie.emplace_back(-1, -1);
    indicator.resize(n);
    
    std::vector<std::string> patterns(n);
    for (int i = 0; i < n; std::cin >> patterns[i], ++i);
    for (const std::string &s : patterns)
    addString(s);
    
    std::string text;
    std::cin >> text;
    
    int j = 0;
    for (const char &c : text) {
        j = getMove(j, c - 'a');
        check(j);
        }
    
    for (const bool &i : indicator)
    std::cout << (i ? "YES" : "NO") << '\n';
    
    return 0;
}

void addString(const std::string &s) {
    int index = 0;
    for (char i : s) {
        char ch = i - 'a';
        if (trie[index].children[ch] == -1) {
            trie[index].children[ch] = (int) trie.size();
            trie.emplace_back(index, ch);
            }
        index = trie[index].children[ch];
        }
    trie[index].isTerminating = true;
    trie[index].numbers.push_back(size++);
}

int getMove(int i, char c) {
    if (trie[i].moves[c] == -1) {
        if (trie[i].children[c] != -1)
        trie[i].moves[c] = trie[i].children[c];
        else {
            if (i == 0)
            trie[i].moves[c] = 0;
            else
            trie[i].moves[c] = getMove(getSuffixLink(i), c);
            }
        }
    
    return trie[i].moves[c];
}

int getSuffixLink(int i) {
    if (trie[i].suffixLink == -1) {
        if (i == 0 || trie[i].parent == 0)
        trie[i].suffixLink = 0;
        else
        trie[i].suffixLink = getMove(getSuffixLink(trie[i].parent), trie[i].symbol);
        }
    
    return trie[i].suffixLink;
}

int getGoodSuffixLink(int i) {
    if (trie[i].goodSuffixLink == -1) {
        int j = getSuffixLink(i);
        
        if (j == 0)
        trie[i].goodSuffixLink = 0;
        else
        trie[i].goodSuffixLink = trie[j].isTerminating ? j : getGoodSuffixLink(j);
        }
    
    return trie[i].goodSuffixLink;
}

void check(int i) {
    for (int j = i; j != 0; j = getGoodSuffixLink(j)) {
        if (trie[j].isTerminating) {
            for (const int &k : trie[j].numbers)
            indicator[k] = true;
            
            trie[j].isTerminating = false;
            }
        }
}