#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include <sstream>

struct Prefix {
    Prefix() = default;

    Prefix(const Prefix &origin) = default;

    Prefix operator+(char c) {
        Prefix prefix(*this);

        if (prefix.string.size() == 2) {
            prefix.prev = std::shared_ptr<Prefix>(new Prefix(prefix));
            prefix.string = c;
        } else {
            prefix.string += c;
        }

        ++prefix.size_;

        return prefix;
    }

    Prefix &operator=(const Prefix &rhs) {
        if (&rhs != this) {
            string = rhs.string;
            prev = rhs.prev;
            size_ = rhs.size_;
        }

        return *this;
    }

    void clear() {
//        string.clear();
//        prev = nullptr;
        size_ = 0;
    }

    size_t size() const {
        return size_;
    }


    friend std::ostream &operator<<(std::ostream &out, const Prefix &prefix) {
        std::stringstream str;

        if (prefix.prev)
            str << *prefix.prev;
        str << prefix.string;

        std::string s = str.str();

        out << s;

        return out;
    }

    friend std::stringstream &operator<<(std::stringstream &out, const Prefix &prefix) {

        if (prefix.prev) {
            out << *prefix.prev;
        }
        out << prefix.string;

        return out;
    }

    std::string string;
    size_t size_ = 0;
    std::shared_ptr<Prefix> prev = nullptr;
};


int main() {
    std::string a;
    std::string b;
    std::cin >> a >> b;

    if (a.size() < b.size())
        std::swap(a, b);

    std::vector<std::vector<Prefix> > prefixes(2,
                                               std::vector<Prefix>(b.size() + 1));

    for (size_t i = 1; i <= a.size(); ++i) {
        prefixes[1][0].clear();
        std::swap(prefixes[0], prefixes[1]);

        for (size_t j = 1; j <= b.size(); ++j) {

            if (a[i - 1] == b[j - 1])
            {
                if (prefixes[0][j - 1].size() + 1 == prefixes[1][j - 1].size()) {
                    prefixes[1][j] = prefixes[1][j - 1];
                } else if (prefixes[0][j - 1].size() + 1 == prefixes[0][j].size()) {
                    prefixes[1][j] = prefixes[0][j];
                } else {
                    prefixes[1][j] = prefixes[0][j - 1] + a[i - 1];
                }
            }
            else if (prefixes[0][j].size() > prefixes[1][j - 1].size())
                prefixes[1][j] = prefixes[0][j];
            else
                prefixes[1][j] = prefixes[1][j - 1];
        }
    }

    std::cout << prefixes[1].back();

    return 0;
}