#ifndef V2_HPP
#define V2_HPP

#include <cmath>
#include <cassert>
#include <string>

// A class representing a 2D vector
class V2 {
    public:
        double x;
        double y;

        V2(const double x, const double y) : x{x}, y{y} {}

        V2() : V2(0, 0) {}

        V2 add(V2 other) {
            return V2(x+other.x, y+other.y);
        }

        V2 sub(V2 other) {
            return V2(x-other.x, y-other.y);
        }

        V2 mul(const double k) {
            return V2(x*k, y*k);
        }

        V2 div(const double k) {
            assert(k != 0);
            return V2(x/k, y/k);
        }

        double mod() {
            return sqrt(x*x + y*y);
        }

        double dot(V2 other) {
            return x*other.x + y*other.y;
        }

        // returns the normalized vector
        V2 norm() {
            const double m = mod();
            return V2(x/m, y/m);
        }

        double dist(V2 other) {
            return sub(other).mod(); // can be optimized without calling sub (because it creates a new temporary V2)
        }

        double distsq(V2 other) {
            V2 diff = sub(other);
            return diff.x*diff.x + diff.y*diff.y;
        }

        // overloaded operators
        V2 operator+(V2 other) {
            return add(other);
        }

        V2 operator-(V2 other) {
            return sub(other);
        }

        V2 operator*(const double k) {
            return mul(k);
        }

        V2 operator/(const double k) {
            return div(k);
        }

        void operator+=(V2 other) {
            x += other.x;
            y += other.y;
        }

        void operator-=(V2 other) {
            x -= other.x;
            y -= other.y;
        }

        std::string to_string() {
            return "V2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }
};

#endif // V2_HPP