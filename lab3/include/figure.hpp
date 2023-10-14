#pragma once
#include <utility>
#include "point.hpp"
#include <iostream>

class Figure {
    public:
        Figure() = default;

        virtual Point center() const = 0;
        virtual double square() const = 0;
        ~Figure() = default;
};
