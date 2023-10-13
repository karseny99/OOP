#include "../include/trapezoid.hpp"
#include "../include/figure.hpp"
#include "../include/point.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <math.h>


bool Trapezoid::trapezoid_check() {
    Point a, b, c, d;
    a = (_array[1] - _array[0]);
    c = (_array[3] - _array[2]);

    b = (_array[2] - _array[1]);
    d = (_array[3] - _array[0]);

    if((a.x / c.x == a.y / c.y) or (d.x / b.x == d.y / b.y)) {
        return true;
    }
    return false;
}

Trapezoid::Trapezoid(Point a, Point b, Point c, Point d) {
    _array = new Point[4];
    _array[0] = a;
    _array[1] = b;
    _array[2] = c;
    _array[3] = d;

    std::sort(_array, _array + 4);

    if(!trapezoid_check()) {
        throw std::logic_error("Invalid coords");
    }
}

Trapezoid::Trapezoid(const Trapezoid& other) {
    _array = new Point[4];
    for(int i = 0; i < 4; ++i) {
        _array[i] = other._array[i];
    }

    if(!trapezoid_check()) {
        throw std::logic_error("Invalid coords");
    }
}

Point Trapezoid::center() const {
    Point center = (_array[0] + _array[1] + _array[2] + _array[3]) / 4;
    return center;
}

double Trapezoid::square() const {

}

bool Trapezoid::equal(const Trapezoid& other) const {
    return (_array[0] == other._array[0]) and (_array[1] == other._array[1]) and (_array[2] == other._array[2]) and (_array[3] == other._array[3]);
}