#pragma once
#include <utility>
#include "point.hpp"
#include <concepts>
#include <iostream>

template<typename T> 
concept figureable = std::is_default_constructible<T>::value || std::integral<T> || std::floating_point<T>;

template<figureable T> 
class Figure {
    public:
        Figure() = default;
        ~Figure() = default;

        virtual Point<T> center() const = 0;
        virtual T square() const = 0;
};
