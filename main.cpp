
#include "scene/bsp_tree.hpp"
#include "tests/test_interception.hpp"
#include "tests/test_vector.hpp"
#include <vector>
#include <iostream>
#include <fstream>

rytg::BSPtree bsp;

std::vector<rytg::Triangle> parseTriangles(){
    size_t N = 0;
    std::fstream f("D:\\RayTraycing\\input.in");
    f >> N;
    std::vector<rytg::Triangle> result(N);
    double x, y, z;
    for(size_t i = 0; i < N; ++i){
        rytg::Point p1, p2, p3;
        f >> x >> y >> z;
        p1 = {x, y, z};
        f >> x >> y >> z;
        p2 = {x, y, z};
        f >> x >> y >> z;
        p3 = {x, y, z};
        result[i] = rytg::Triangle(p1, p2, p3);
        rytg::Triangle* T = new rytg::Triangle(result[i]);
        bsp.add(T);
    }
    return result;
}


int main(){
    test_rytg::test_vector();
    test_rytg::test_interception();
    auto v = parseTriangles();
    //rytg::BSPtree bsp(v);

    return 0;
}
