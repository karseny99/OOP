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
        if(a * a > 0 and b * b > 0 and c * c > 0 and d * d > 0) {
            return true;
        }
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

Rectangle::Rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    _array = new Point[4];
    _array[0].x = x1;
    _array[0].y = y1;
    _array[1].x = x2;
    _array[1].y = y2;
    _array[2].x = x3;
    _array[2].y = y3;
    _array[3].x = x4;
    _array[3].y = y4;
    
    std::sort(_array, _array + 4);

    if(!rectangle_check()) {
        throw std::logic_error("Invalid coords");
    }
}
 
Point Rectangle::center() const {

    if(_array == nullptr) {
        throw std::logic_error("Can't get center of None-Figure");
    }

    Point res;
    res = (_array[3] - _array[0]) / 2; 
    return res;
}

double Rectangle::square() const {
        if(_array == nullptr) return 0;
        return vector_length(_array[1]- _array[0]) * vector_length(_array[2] - _array[0]);
}

bool Rectangle::equal(const Rectangle& other) const { // better to not to use
    if(_array == nullptr and other._array == nullptr) {
        return true;
    } else if(other._array != nullptr and _array != nullptr) {
        return (other._array[0] == _array[0]) and (other._array[1] == _array[1]) and (other._array[2] == _array[2]) and (other._array[3] == _array[3]);
    }
    return false;
}

Rectangle::operator double() const {
    return square();
}

bool operator==(Rectangle& left_operand, Rectangle& right_operand) {
    if(left_operand._array == nullptr and right_operand._array == nullptr) {
        return true;
    } else if(left_operand._array != nullptr and right_operand._array != nullptr) {
        return (left_operand._array[0] == right_operand._array[0]) and (left_operand._array[1] == right_operand._array[1]) and (left_operand._array[2] == right_operand._array[2]) and (left_operand._array[3] == right_operand._array[3]);
    }
    return false;
}
