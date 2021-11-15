#ifndef TEST_AABB_HPP
#define TEST_AABB_HPP

#include "polygon/triangle.hpp"
#include "geo/aabb.hpp"
#include "geo/point.hpp"
#include <iostream>

namespace test_rytg {

void test_aabb(){
    rytg::Triangle t1 = rytg::Triangle({1, 2, 3}, {2, 1, 4}, {5, 0, 1});
    rytg::Triangle t2 = rytg::Triangle({2, 3, 4}, {3, 2, 5}, {8, 8, 7});
    rytg::Triangle t3 = rytg::Triangle({10, 15, 16}, {20, 10, 13}, {17, 15, 8});
    rytg::Point p1 = {6, 6, 6};
    rytg::Point p2 = {7, 7, 7};
    rytg::Point p3 = {8, 8, 7.0000001};
    rytg::Point p4 = {9, 9, 7.00001};
    rytg::Aabb aabb1 = rytg::Aabb(t1, 2);
    rytg::Aabb aabb2 = rytg::Aabb(t2);
    rytg::Aabb aabb3 = rytg::Aabb(t3, 0);

    assert(aabb1.isIntersection(aabb2));
    assert(!aabb1.isIntersection(aabb3));
    assert(!aabb2.isIntersection(aabb3));

    assert(aabb1.isInBox(p1));
    assert(aabb2.isInBox(p1));
    assert(aabb2.isInBox(p2));
    assert(aabb2.isInBox(p3));
    assert(!aabb2.isInBox(p4));
    assert(!aabb3.isInBox(p1));
/*
    std::cout << "intersection_result12:" << aabb1.isIntersection(aabb2) <<'\n';
    std::cout << "intersection_result13:" << aabb1.isIntersection(aabb3) <<'\n';
    std::cout << "intersection_result23:" << aabb2.isIntersection(aabb3) <<'\n';

    std::cout << "point_in_box_result1:" << aabb1.isInBox(p1) <<'\n';

    std::cout << "point_in_box_result21:" << aabb2.isInBox(p1) <<'\n';
    std::cout << "point_in_box_result22:" << aabb2.isInBox(p2) <<'\n';
    std::cout << "point_in_box_result23:" << aabb2.isInBox(p3) <<'\n';
    std::cout << "point_in_box_result24:" << aabb2.isInBox(p4) <<'\n';

    std::cout << "point_in_box_result3:" << aabb3.isInBox(p1) <<'\n';
*/
}

}

#endif