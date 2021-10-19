
#include "scene/bsp_tree.hpp"
#include "tests/test_interception.hpp"
#include "tests/test_vector.hpp"
#include <vector>
#include <iostream>
#include <fstream>

rytg::BSPtree bsp;

void parseTriangles(){
    size_t N = 0;
    std::fstream f("D:\\RayTraycing\\input.in");
    f >> N;
    double x, y, z;
    for(size_t i = 0; i < N; ++i){
        rytg::Point p1, p2, p3;
        f >> x >> y >> z;
        p1 = {x, y, z};
        f >> x >> y >> z;
        p2 = {x, y, z};
        f >> x >> y >> z;
        p3 = {x, y, z};
        rytg::Triangle* T = new rytg::Triangle(p1, p2, p3);
        bsp.add(T);
    }
}


int main(){
    test_rytg::test_vector();
    test_rytg::test_interception();
    parseTriangles();
    //rytg::BSPtree bsp(v);

    return 0;
}
