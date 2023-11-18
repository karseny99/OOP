
#include <iostream>
#include <memory>
#include <chrono>
#include <list>
#include <map>
#include <utility>
#include <list>
#include "../include/Allocator.hpp"
#include <vector>
#include "../include/DynamicArray.hpp"
#include <stdexcept>


template <int N>
int factorial()
{
    return N * factorial<N - 1>();
}
template <>
int factorial<0>()
{
    return 1;
}


template <int N>
void fill_map(std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>, 10>> &map)
{
    map.insert(std::pair<int, int>(N, factorial<N>()));
    fill_map<N - 1>(map);
}


template <>
void fill_map<0>(std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>, 10>> &map)
{
    map.insert(std::pair<int, int>(0, factorial<0>()));
}


int main(int argc, char **argv)
{
    // DynamicArray<int, std::less<int>, Allocator<int, 10>> myvec;
    DynamicArray<int, Allocator<int, 10>> myvec;

    for(size_t i{0}; i < 10; ++i) {
        myvec.push_back(i);
    }

    myvec[0] = -20;
    myvec.erase(4);

    std::vector<int> ds;

    // std::iterator<std::forward_iterator_tag, 10> it;

    for(size_t i{0}; i < 9; ++i) {
        std::cout << myvec[i] << ' ';
    }
    
    std::cout << std::endl;
    std::cout << '\n';

    // auto it1 = myvec.begin();
    // std::cout << *it1 << ' ' << '\n';

    for(auto it = myvec.begin(); it != myvec.end(); ++it) {
        std::cout << *it << ' ';
    } 

    std::cout << '\n';
    std::cout << '\n';
    std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>, 10>> my_map;

    // std::cout << my_map.size() << std::endl;

    fill_map<9>(my_map);

    for(auto& el : my_map) {
        std::cout << el.first << ' ' << el.second << std::endl;
    }
}