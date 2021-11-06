#ifndef TEST_BSP_HPP
#define TEST_BSP_HPP

#include "scene/bsp_tree.hpp"
#include "polygon/triangle.hpp"
#include <sstream>
#include <cassert>

namespace test_rytg {

void test_no_intersection(){
    std::ostringstream oss;
    rytg::BSPtree bsp(oss);
    {
    rytg::Triangle* t1 = new rytg::Triangle({0, 0 ,0}, {1, 1, 1}, {1, 0, 0});
    rytg::Triangle* t2 = new rytg::Triangle({10, 10, 10}, {20, 20, 20}, {30, 30, 30});
    bsp.add(t1);
    bsp.add(t2);
    }
    assert(oss.str().empty());
    //std::cout << "BSP - no intersection done\n";
}

void test_one_point(){
    std::ostringstream oss;
    {
    rytg::BSPtree bsp(oss);
    rytg::Triangle* t1 = new rytg::Triangle({0, 0 ,0}, {1, 1, 1}, {1, 0, 0});
    rytg::Triangle* t2 = new rytg::Triangle({0, 0, 0}, {0, 1, 0}, {0, 1, -1});
    rytg::Triangle* t3 = new rytg::Triangle({0, 0, 0}, {-1, 0, 0}, {-1, 0, 1});
    bsp.add(t1);
    bsp.add(t2);
    bsp.add(t3);
    }
    assert(oss.str() == "0\n1\n2\n");
    //std::cout << "BSP - one point done\n";
}

void test_edge(){
    std::ostringstream oss;
    {
    rytg::BSPtree bsp(oss);
    rytg::Triangle* t1 = new rytg::Triangle({0, 0 ,0}, {1, 0, 0}, {1, 0, 1});
    rytg::Triangle* t2 = new rytg::Triangle({0, 0, 0}, {1, 0, 0}, {1, 1, 0});
    rytg::Triangle* t3 = new rytg::Triangle({1, 0, 0}, {1, 0, 1}, {2, 0, 0});
    bsp.add(t1);
    bsp.add(t2);
    bsp.add(t3);
    }
    assert(oss.str() == "0\n1\n2\n");
    //std::cout << "BSP - edge done\n";
}


void test_bsp(){
    test_no_intersection();
    test_one_point();
    test_edge();
}
}




#endif
