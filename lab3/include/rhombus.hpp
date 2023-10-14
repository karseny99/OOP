#pragma once
#include "figure.hpp"
#include "point.hpp"
#include <iostream>

class Rhombus : public Figure {
    
    friend std::istream& operator>>(std::istream& is, Rhombus& r);
    friend std::ostream& operator<<(std::ostream& os, Rhombus& r);
    friend bool operator==(Rhombus& left_operand, Rhombus& right_operand);

    public:
        Rhombus() = default;
        Rhombus(Point a, Point b, Point c, Point d);
        Rhombus(const Rhombus& other);
        Rhombus(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
        ~Rhombus() = default;

        operator double() const;


        virtual Point center() const final;
        virtual double square() const final;
        bool equal(const Rhombus& other) const;

    private:
        Point * _array = nullptr;

        bool rhombus_check();
};

inline std::istream& operator>>(std::istream& is, Rhombus& r) {
    if(r._array == nullptr) {
        r._array = new Point[4];
    }
    
    is >> r._array[0].x >> r._array[0].y >> r._array[1].x >> r._array[1].y >> \
        r._array[2].x >> r._array[2].y >> r._array[3].x >> r._array[3].y;


    std::sort(r._array, r._array + 4);
    if(!r.rhombus_check()) {
        throw std::logic_error("Invalid coords");
    }

    return is;
}   

inline std::ostream& operator<<(std::ostream& os, Rhombus& r) {
    if(r._array == nullptr) {
        os << "Cannot display None-Figure" << std::endl;
        return os;
    }
    
    for(int i = 0; i < 4; ++i) {
        os << "dot" << i + 1 << "[" << r._array[i].x << ", " << r._array[i].y << "]" << std:: endl;
    }

    return os;
}