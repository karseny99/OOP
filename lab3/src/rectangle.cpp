#include "../include/rectangle.hpp"
#include "../include/figure.hpp"
#include "../include/point.hpp"
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

bool Rectangle::rectangle_check() {
    Point a, b, c, d;
    a = (_array[1] - _array[0]);
    b = (_array[2] - _array[0]);
    c = (_array[3] - _array[2]);
    d = (_array[3] - _array[1]);

    if(a * b == 0 and b * c == 0 and c * d == 0 and a * d == 0) {
        return true;
    }
    return false;
}

Rectangle::Rectangle(Point a, Point b, Point c, Point d) {
    _array = new Point[4];
    _array[0] = a;
    _array[1] = b;
    _array[2] = c;
    _array[3] = d;

    std::sort(_array, _array + 4);

    if(!rectangle_check()) {
        throw std::logic_error("Invalid coords");
    }
}

Rectangle::Rectangle(const Rectangle& other) {
    _array = new Point[4];
    for(int i = 0; i < 4; ++i) {
        _array[i] = other._array[i];
    }

    if(!rectangle_check()) {
        throw std::logic_error("Invalid coords");
    }
}
 
Point Rectangle::center() const {
    Point res;
    res = (_array[3] - _array[0]) / 2; 
    return res;
}

double Rectangle::square() const {
    return fabs((_array[0].x - _array[1].x) * (_array[0].y - _array[2].y));
}

bool Rectangle::equal(const Rectangle& other) const { 
    return (_array[0] == other._array[0]) and (_array[1] == other._array[1]) and (_array[2] == other._array[2]) and (_array[3] == other._array[3]);
}