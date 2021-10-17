#include "../polygon/triangle.hpp"
#include <cassert>
#include <iostream>

namespace test_rytg{

void self(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 0.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    auto t2 = t1;
    //assert(t2.isIntersection(t1));
    std::cout << "self done\n";
}

void normal(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 0.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    rytg::Triangle t2(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 1.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    //assert(t2.isIntersection(t1));
    std::cout << "normal done\n";
}

void test_interception(){
    self();
    normal();
}

}