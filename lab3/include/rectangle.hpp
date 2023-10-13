#pragma once
#include "figure.hpp"
#include "point.hpp"
#include <utility>

class Rectangle : public Figure {

    public:
        Rectangle() = default;
        Rectangle(Point a, Point b, Point c, Point d);
        Rectangle(const Rectangle& other);

        ~Rectangle() = default;

        virtual Point center() const final;
        virtual double square() const final;
        bool equal(const Rectangle& other) const;

    private:
        Point * _array;

        bool rectangle_check();
};