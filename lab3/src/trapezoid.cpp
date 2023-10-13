#include "../include/trapezoid.hpp"
#include "../include/figure.hpp"
#include "../include/point.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <math.h>

static double sq_formula(double a, double b, double c, double d) { // a || b
    double s = (a + b) / 2 * sqrt(c * c - (((a - b) * (a - b) + c * c - d * d) / (2 * (a  - b))) * (((a - b) * (a - b) + c * c - d * d) / (2 * (a  - b))));
    return s;
}

bool Trapezoid::trapezoid_check() {
    Point a, b, c, d, e, f;
    a = (_array[1] - _array[0]);
    c = (_array[3] - _array[2]);

    b = (_array[2] - _array[1]);
    d = (_array[3] - _array[0]);

    e = (_array[3] - _array[1]);
    f = (_array[2] - _array[0]);

    if((a.x / c.x == a.y / c.y) and (e.x / f.x != e.y / f.y)) {
        
        return true;
    }
    if((d.x / b.x == d.y / b.y) and (a.x / c.x != a.y / c.y)) {

        return true;
    }
    if((e.x / f.x == e.y / f.y) and (a.x / c.x != a.y / c.y)) {
        
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
    if(_array == nullptr) {
        throw std::logic_error("Cannot get center of None-figure");
    }
    Point center = (_array[0] + _array[1] + _array[2] + _array[3]) / 4;
    return center;
}

double Trapezoid::square() const {

    if(_array == nullptr) {
        return 0;
    }

    Point a, b, c, d, e, f;

    a = (_array[1] - _array[0]);
    c = (_array[3] - _array[2]);

    b = (_array[2] - _array[1]);
    d = (_array[3] - _array[0]);

    e = (_array[3] - _array[1]);
    f = (_array[2] - _array[0]);


    if(a.x / c.x == a.y / c.y) {
        b = _array[3] - _array[1];
        d = _array[2] - _array[0];

        return sq_formula(vector_length(a), vector_length(c), vector_length(b), vector_length(d));

    } else if(d.x / b.x == d.y / b.y) {
        a = _array[1] - _array[0];
        c = _array[3] - _array[2];

        return sq_formula(vector_length(b), vector_length(d), vector_length(a), vector_length(c));
     
    } else if(e.x / f.x == e.y / f.y) {
        a = _array[1] - _array[0];
        b = _array[3] - _array[2];

        return sq_formula(vector_length(e), vector_length(f), vector_length(a), vector_length(b));
    }
}

bool Trapezoid::equal(const Trapezoid& other) const {
    return (_array[0] == other._array[0]) and (_array[1] == other._array[1]) and (_array[2] == other._array[2]) and (_array[3] == other._array[3]);
}