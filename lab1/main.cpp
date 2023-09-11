#include <iostream>
#include "box_cap.h"


int main() {
    unsigned int l, w, h;
    std::cout << "Enter length, width and height of room:\n";
    std::cin >> l >> w >> h;
    
    std::cout << box_capacity(l, w, h) << '\n';
}