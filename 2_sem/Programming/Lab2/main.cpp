#include <iostream>
#include <utility>
#include <vector>

template <typename T>
class Poly {
    std::vector<T> coefficients;

public:
    int size() {
        return coefficients.size();
    }

    T coefficient(int number) {
        if (number < size()) {
            return coefficients[number];
        } else {
            return 0;
        }
    }

    void add(int number, T value) {
        if (number < size()) {
            coefficients[number] += value;
        } else {
            coefficients.resize(number + 1, 0);
            coefficients[number] = value;
        }
    }

    T substitute(T x) {
        T sum = 0;

        for (auto c : coefficients) {
            sum += c * x;
        }

        return sum;
    }

    Poly(std::vector<T> c) : coefficients(std::move(c)) {};

    Poly(const Poly &origin) : coefficients(origin.coefficients) {};

    Poly() : coefficients(std::vector<T> ()) {};

    template<typename S>
    Poly<T> (const Poly<S> & p) : coefficients(std::vector<T> ()) {

    }

    ~Poly() {
        coefficients.resize(0);
        std::cout << "Destructor's work have been done" << std::endl;
    }

    bool operator==(Poly &rhs) {
        for (int i = 0; i < coefficients.size(); i++) {
            if (i < rhs.size()) {
                if (coefficients[i] != rhs.coefficients[i]) {
                    return false;
                }
            } else {
                if (coefficients[i] != 0) {
                    return false;
                }
            }
        }

        return true;
    }

    Poly operator+(Poly &rhs) {
        Poly buffer;

        if (coefficients.size() >= rhs.size()) {
            buffer = Poly(coefficients);

            for (int i = 0; i < rhs.size(); i++) {
                buffer.add(i, rhs.coefficient(i));
            }
        } else {
            buffer = Poly(rhs.coefficients);

            for (int i = 0; i < coefficients.size(); i++) {
                buffer.add(i, coefficients[i]);
            }
        }

        return buffer;
    }

    Poly operator-() {
        Poly buffer(coefficients);

        for (int i = 0; i < size(); i++) {
            buffer.coefficients[i] = -coefficients[i];
        }

        return buffer;
    }

    Poly operator-(Poly &rhs) {
        Poly buffer(-rhs);

        return *this + buffer;
    }

    void operator +=(Poly &rhs) {
        *this = *this + rhs;
    }

    void operator-=(Poly &rhs) {
        *this = *this - rhs;
    }

    Poly operator*(T &rhs) {
        Poly buffer(coefficients);

        for (int i = 0; i < size(); i++) {
            buffer.coefficients[i] *= rhs;
        }

        return buffer;
    }
    Poly operator/(T &rhs) {
        Poly buffer(coefficients);

        for (int i = 0; i < size(); i++) {
            buffer.coefficients[i] /= rhs;
        }

        return buffer;
    }

    void operator*=(T &rhs) {
        for (int i = 0; i < size(); i++) {
            coefficients[i] *= rhs;
        }
    }
    void operator/=(T &rhs) {
        for (int i = 0; i < size(); i++) {
            coefficients[i] /= rhs;
        }
    }

    T operator[](int i) {
        return coefficients[i];
    }
};


template <typename T>
std::istream& operator>>(std::istream &in, Poly<T> &p) {
    T buffer;

    if (in >> buffer) {
        p.add(p.size(), buffer);
    } else {
        std::cout << "Given value has inappropriate type" << '\n';
    }
}
template <typename T>
std::ostream& operator<<(std::ostream &out, Poly<T> &p) {
    for (int i = 0; i < p.size(); i++) {
        if (p[i] < 0) {
            if (i != 0) {
                out << "- ";
            } else {
                out << "-";
            }
        } else {
            if (i != 0) {
                out << "+ ";
            }
        }

        out << abs(p[i]);
        if (i > 0) {
            out << 'x';
            if (i > 1) {
                out << '^' << i;
            }
        }

        out << ' ';
    }

    return out;
}


int main() {
    Poly<int> pInt(std::vector<int> {-1, 2, 3, -4});
    Poly<int> pInt2(std::vector<int> {-1, 2, 3, -5});
    Poly<double> pD(std::vector<double> {-1, 2, 3, -4});


    std::cout << pInt << '\n';
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
