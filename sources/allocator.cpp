#include <iostream>
#include <map>

#include "factorial.hpp"
#include "reserving_allocator.hpp"
#include "custom_container.hpp"

// ------------------------------------------------------------------
int main( int, char** ) {
    constexpr size_t size = 10;

    std::map<size_t, size_t> m;
    for (size_t i = 0; i < size; ++i) {
        m.insert({i, math::factorial(i)});
    }

    for (const auto& item: m) {
        std::cout << item.first << " " << item.second << std::endl;
    }

    std::map<size_t, 
             size_t, 
             std::less<size_t>, 
             allocators::reserving_allocator<std::pair<const size_t, size_t>, size>> rm;
    for (size_t i = 0; i < size; ++i) {
        rm.insert({i, math::factorial(i)});
    }

    for (const auto& item: rm) {
        std::cout << item.first << " " << item.second << std::endl;
    }

    containers::custom_container<int> cc;
    for (size_t i = 0; i < size; ++i) {
        cc.push_back(i);
    }

    for (size_t i = 0, sz = cc.size(); i < sz; ++i) {
        std::cout << cc.get(i) << std::endl;
    }    

    containers::custom_container<int, allocators::reserving_allocator<int, size>> rcc;
    for (size_t i = 0; i < size; ++i) {
        rcc.push_back(i);
    }

    for (size_t i = 0, sz = cc.size(); i < sz; ++i) {
        std::cout << cc.get(i) << std::endl;
    }    

    return 0;
}