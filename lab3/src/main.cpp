#include <bits/stdc++.h>
#include "../include/figure.hpp"
#include "../include/rectangle.hpp"
#include "../include/trapezoid.hpp"
#include "../include/rhombus.hpp"

int main() {
    Point a = {-4, -1};
    Point b = {-2, 5};
    Point c = {4, 8};
    Point d = {8, 5};
    Trapezoid h(a, b, c, d);
    std::cout << h.square() << '\n';
}