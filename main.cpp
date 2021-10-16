
#include "scene/bsp_tree.hpp"
#include "tests/test_interception.hpp"
#include <vector>
#include <iostream>

std::vector<rytg::Triangle> parseTriangles(){
    size_t N = 0;
    std::cin >> N;
    std::vector<rytg::Triangle> result(N);
    double x, y, z;
    for(size_t i = 0; i < N; ++i){
        rytg::Point p1, p2, p3;
        std::cin >> x >> y >> z;
        p1 = {x, y, z};
        std::cin >> x >> y >> z;
        p2 = {x, y, z};
        std::cin >> x >> y >> z;
        p3 = {x, y, z};
        result[i] = rytg::Triangle(p1, p2, p3);
    }
    return result;
}


int main(){
    //auto v = parseTriangles();
    //rytg::BSPtree bsp(v);
   // int x;
    test_rytg::test_interception();
    return 0;
}
