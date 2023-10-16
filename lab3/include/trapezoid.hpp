#pragma once
#include "figure.hpp"
#include "point.hpp"
#include <iostream>


class Trapezoid : public Figure {

    friend std::istream& operator>>(std::istream& is, Trapezoid& r);
    friend std::ostream& operator<<(std::ostream& os, Trapezoid& r);
    friend bool operator==(Trapezoid& left_operand, Trapezoid& right_operand);

    public:
        Trapezoid() = default;
        Trapezoid(Point a, Point b, Point c, Point d);
        Trapezoid(const Trapezoid& other);
        Trapezoid(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
        ~Trapezoid() = default;

        operator double() const;

        void operator=(Trapezoid& r) {
            if(r._array == nullptr) {
                if(_array != nullptr) {
                    delete[] _array;
                    delete[] _original_array;
                }
                _original_array = nullptr;
                _array = nullptr;
                return;
            }

            if(_array == nullptr) {
                _array = new Point[4];
                _original_array = new Point[4];
            }

            for(int i = 0; i < 4; ++i) {
                _original_array[i] = r._original_array[i];
                _array[i] = r._array[i];
            }
            return;
        }


        virtual Point center() const final;
        virtual double square() const final;

    private:
        Point * _array = nullptr;
        Point * _original_array = nullptr;

        bool trapezoid_check();
};

inline std::istream& operator>>(std::istream& is, Trapezoid& r) {
    if(r._array == nullptr) {
        r._array = new Point[4];
    }
    
    is >> r._array[0].x >> r._array[0].y >> r._array[1].x >> r._array[1].y >> \
        r._array[2].x >> r._array[2].y >> r._array[3].x >> r._array[3].y;


    if(!r.trapezoid_check()) {
        throw std::logic_error("Invalid coords");
    }

    std::sort(r._array, r._array + 4);
    return is;
}   

inline std::ostream& operator<<(std::ostream& os, Trapezoid& r) {
    if(r._array == nullptr) {
        os << "Cannot display None-Figure" << std::endl;
        return os;
    }
    
    for(int i = 0; i < 4; ++i) {
        os << "dot" << i + 1 << "[" << r._original_array[i].x << ", " << r._original_array[i].y << "]" << std:: endl;
    }

    return os;
}