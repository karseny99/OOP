#pragma once
#include "figure.hpp"
#include "point.hpp"
#include <utility>
#include <iostream>


class Rectangle : public Figure {

    friend std::istream& operator>>(std::istream& is, Rectangle& r);
    friend std::ostream& operator<<(std::ostream& os, Rectangle& r);
    friend bool operator==(Rectangle& left_operand, Rectangle& right_operand);


    public:
        Rectangle() = default;
        Rectangle(Point a, Point b, Point c, Point d);
        Rectangle(const Rectangle& other);
        Rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
        ~Rectangle() = default;

        operator double() const;


        virtual Point center() const final;
        virtual double square() const final;
        bool equal(const Rectangle& other) const;

    private:
        Point * _array = nullptr;
        bool rectangle_check();
};

inline std::istream& operator>>(std::istream& is, Rectangle& r) {
    if(r._array == nullptr) {
        r._array = new Point[4];
    }
    
    is >> r._array[0].x >> r._array[0].y >> r._array[1].x >> r._array[1].y >> \
        r._array[2].x >> r._array[2].y >> r._array[3].x >> r._array[3].y;


    std::sort(r._array, r._array + 4);
    if(!r.rectangle_check()) {
        throw std::logic_error("Invalid coords");
    }

    return is;
}   

inline std::ostream& operator<<(std::ostream& os, Rectangle& r) {
    if(r._array == nullptr) {
        os << "Cannot display None-Figure" << std::endl;
        return os;
    }
    
    for(int i = 0; i < 4; ++i) {
        os << "dot" << i + 1 << "[" << r._array[i].x << ", " << r._array[i].y << "]" << std:: endl;
    }

    return os;
}