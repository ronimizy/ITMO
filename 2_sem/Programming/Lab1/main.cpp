#include <iostream>
#include <vector>
#include <cmath>

class Point {
public:
    double x, y;

    Point(double x = 0, double y = 0)
            : x(x), y(y) {}

    Point(const Point &origin)
            : x(origin.x), y(origin.y) {}

    double distanceFrom(Point point) {
        return sqrt(pow(x - point.x, 2) + pow(y - point.y, 2));
    }

    double lenFromCenter() {
        return distanceFrom(Point());
    }

    Point normal() {
        return Point(y, -x);
    }

    Point operator+(const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }

    Point operator-(const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }

    Point operator-() {
        return Point(-x, -y);
    }

    void operator+=(const Point &rhs) {
        x += rhs.x;
        y += rhs.y;
    }

    void operator-=(const Point &rhs) {
        x -= rhs.x;
        y -= rhs.y;
    }
};

class PolygonalLine {
public:
    std::vector<Point> points;

    PolygonalLine(const std::vector<Point> &points)
            : points(points) {}

    PolygonalLine(const PolygonalLine &origin)
            : points(origin.points) {}

    virtual double perimeter() {
        double sum = 0;

        for (int i = 1; i < points.size(); i++) {
            sum += points[i].distanceFrom(points[i - 1]);
        }

        return sum;
    }

    int vertexCount() const {
        return points.size();
    }
};

class ClosedPolygonalLine : public PolygonalLine {
public:
    ClosedPolygonalLine(const std::vector<Point> &points)
            : PolygonalLine(points) {}

    ClosedPolygonalLine(const ClosedPolygonalLine &origin)
            : PolygonalLine(origin.points) {}

    double perimeter() override {
        double sum = 0;

        for (int i = 0; i < points.size(); i++) {
            sum += points[i].distanceFrom(points[(i - 1 + points.size()) % points.size()]);
        }

        return sum;
    }
};

class ConvexPolygon : public ClosedPolygonalLine {
public:
    ConvexPolygon(const std::vector<Point> &points)
            : ClosedPolygonalLine(points) {
        if (!isConvex()) {
            this->points.resize(0);
        }
    }

    ConvexPolygon(const ConvexPolygon &origin)
            : ClosedPolygonalLine(origin.points) {}

    virtual double area() {
        double sum = 0;

        for (int i = 0; i < points.size(); i++) {
            sum += points[i].x * (points[(i + 1 + points.size()) % points.size()].y -
                                  points[(i - 1 + points.size()) % points.size()].y);
        }

        return abs(sum) / 2;
    }

private:
    bool isConvex() {
        std::vector<std::pair<Point, Point>> edges;
        std::vector<Point> normals;

        edges.resize(0);
        normals.resize(0);

        for (int i = 1; i < points.size(); i++) {
            edges.emplace_back(points[i - 1], points[i]);
        }
        edges.emplace_back(points[points.size() - 1], points[0]);

        for (int i = 0; i < points.size(); i++) {
            normals.push_back((edges[i].second - edges[i].first).normal());
        }

        for (int i = 0; i < points.size(); i++) {
            double A = normals[i].x, B = normals[i].y, C = A * edges[i].first.x + B * edges[i].first.y;

            bool direction;

            for (auto &point : points) {
                if (A * point.x + B * point.y - C != 0) {
                    direction = A * point.x + B * point.y - C > 0;
                }
            }

            for (auto &point : points) {
                if (A * point.x + B * point.y - C != 0 && (A * point.x + B * point.y - C > 0) != direction) {
                    return false;
                }
            }
        }

        return true;
    }

    double determinant(const std::vector<std::vector<double>> arr) {
        return arr[0][0] * (arr[1][1] * arr[2][2] - arr[1][2] * arr[2][1])
               - arr[0][1] * (arr[1][0] * arr[2][2] - arr[2][0] * arr[1][2])
               + arr[0][2] * (arr[1][0] * arr[2][1] - arr[2][0] * arr[1][1]);
    }
};

class Triangle : public ConvexPolygon {

public:
    Triangle(const std::vector<Point> &points) : ConvexPolygon(points) {
        if (points.size() != 3) {
            this->points.resize(0);
        }
    }

    Triangle(const Triangle &origin)
            : ConvexPolygon(origin.points) {}
};

class Trapeze : public ConvexPolygon {

public:
    Trapeze(const std::vector<Point> &points) : ConvexPolygon(points) {
        if (points.size() != 4 || !isTrapeze()) {
            this->points.resize(0);
        }
    }

    Trapeze(const Trapeze &origin) : ConvexPolygon(origin.points) {}

private:
    bool isTrapeze() {
        std::vector<Point> directionals;
        std::vector<std::pair<int, int>> parallels;

        directionals.resize(0);

        for (int i = 1; i < 4; i++) {
            directionals.push_back(points[i] - points[i - 1]);
        }
        directionals.push_back(points[0] - points[3]);

        for (int i = 0; i < directionals.size() - 1; i++) {
            for (int j = i + 1; j < directionals.size(); j++) {
                if (((directionals[i].x * directionals[j].x + directionals[i].y * directionals[j].y) /
                     directionals[i].lenFromCenter() * directionals[j].lenFromCenter()) == 0
                    or ((directionals[i].x * directionals[j].x + directionals[i].y * directionals[j].y) /
                        directionals[i].lenFromCenter() * directionals[j].lenFromCenter()) == 180) {
                    parallels.emplace_back(i, j);
                }
            }
        }

        if (parallels.size() != 1) {
            return false;
        }

        return true;
    }
};

class AppropriatePolygon : public ConvexPolygon {
public:
    AppropriatePolygon(const std::vector<Point> &points) : ConvexPolygon(points) {
        if (!isAppropriate()) {
            this->points.resize(0);
        }
    }

    AppropriatePolygon(const AppropriatePolygon &origin) : ConvexPolygon(origin.points) {}

private:
    bool isAppropriate() {
        double length = points[0].distanceFrom(points[1]);

        for (int i = 2; i < points.size(); i++) {
            if (points[i].distanceFrom(points[i - 1]) != length) {
                return false;
            }
        }

        double cos = ((double) points.size() - 2) * 180 / points.size();

        for (int i = 1; i < points.size() - 1; i++) {
            Point v1 = points[i - 1] - points[i], v2 = points[i + 1] - points[i];

            if (fmod(((v1.x * v2.x + v1.y * v2.y) / v1.lenFromCenter() * v2.lenFromCenter()), cos) != 0) {
                return false;
            }
        }
        Point v1 = points[points.size() - 1] - points[0], v2 = points[1] - points[0];

        if (fmod(((v1.x * v2.x + v1.y * v2.y) / v1.lenFromCenter() * v2.lenFromCenter()), cos) != 0) {
            return false;
        }

        return true;
    }
};

int main() {
    Point p1(1, 0);
    Point p2(2, 0);

    PolygonalLine line(std::vector<Point>{p1, p2, Point(3, 0)});

    std::cout << line.perimeter() << ' ' << line.vertexCount() << '\n'; // 2 3

    ConvexPolygon cp(std::vector<Point>{Point(), Point(1, 0), Point(1, 1), Point(0, 1)});
    ConvexPolygon np(std::vector<Point>{Point(), Point(1, 0), Point(0.5, 0.5), Point(1, 1), Point(0, 1)});

    std::cout << cp.area() << ' ' << cp.perimeter() << '\n'; // 1
    std::cout << np.area() << '\n'; // 0

    Triangle cT(std::vector<Point>{Point(0, 1), Point(), Point(1, 0)});
    Triangle nT(std::vector<Point>{Point(0, 1), Point()});

    std::cout << cT.area() << ' ' << cT.perimeter() << '\n'; //0.5 3.41....
    std::cout << nT.area() << ' ' << nT.perimeter() << '\n'; // 0 0

    Trapeze cTr(std::vector<Point>{Point(0, 1), Point(-1, 0), Point(2, 0), Point(1, 1)});
    Trapeze nTr(std::vector<Point>{Point(0, 1), Point(), Point(1, 0), Point(1, 2)});

    std::cout << cTr.area() << ' ' << cTr.perimeter() << '\n'; //2 6.82...
    std::cout << nTr.area() << ' ' << nTr.perimeter() << '\n'; // 0 0

    AppropriatePolygon cAp(std::vector<Point>{Point(), Point(0, 1), Point(1, 1), Point(1, 0)});
    AppropriatePolygon nAp(std::vector<Point>{Point(), Point(0, 1), Point(1, 1), Point(0.9, 0)});

    std::cout << cAp.area() << ' ' << cAp.perimeter() << '\n'; //2 6.82...
    std::cout << nAp.area() << ' ' << nAp.perimeter() << '\n'; // 0 0

    PolygonalLine* arr[] = {&line, &cp, &cT, &cTr, &cAp};
    std::cout << '\n';
    for (auto i : arr) {
        std::cout << i->perimeter() << '\n';
    }

    return 0;
}
