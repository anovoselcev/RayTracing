#include "../polygon/triangle.hpp"
#include <cassert>
#include <iostream>

namespace test_rytg{

void self(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 0.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    auto t2 = t1;
    assert(t2.isIntersection(&t1));
    std::cout << "self done\n";
}

void normal(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 0.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    rytg::Triangle t2(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 1.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    assert(t2.isIntersection(&t1));
    std::cout << "normal done\n";
}

void onePoint(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 0.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    rytg::Triangle t2(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 1.0, 0.0}, rytg::Point{0.0, 1.0, -1.0});
    assert(t2.isIntersection(&t1));
    std::cout << "onePoint done\n";
}

void notIntersect(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 1.0, 0.0}, rytg::Point{1.0, 0.0, 0.0});
    rytg::Triangle t2(rytg::Point{0.0, 0.0, 1.0}, rytg::Point{0.0, 0.0, 2.0}, rytg::Point{0.0, -1.0, 1.0});
    assert(!t2.isIntersection(&t1));
    std::cout << "notIntersect done\n";
}

// Some cases in one plane:
// the second trig is small
void planeIntersect1(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 0.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    rytg::Triangle t2(rytg::Point{0.8, 0.0, 0.7}, rytg::Point{1.0, 0.0, 0.3}, rytg::Point{1.5, 0.0, 0.9});
    assert(!t2.isIntersection(&t1));
    std::cout << "planeIntersect1 done\n";
}
// the second trig is big
void planeIntersect2(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.0, 0.0, 1.0}, rytg::Point{1.0, 0.0, 0.0});
    rytg::Triangle t2(rytg::Point{20, 0.0, 10}, rytg::Point{39, 0.0, 30}, rytg::Point{50, 0.0, 40});
    assert(!t2.isIntersection(&t1));
    std::cout << "planeIntersect2 done\n";
}
// one trig in another
void planeIntersect3(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 0.0}, rytg::Point{0.5, 1.0, 0.0}, rytg::Point{1.0, 0.0, 0.0});
    rytg::Triangle t2(rytg::Point{0.25, 0.0, 0.0}, rytg::Point{0.5, 0.5, 0.0}, rytg::Point{0.5, 0.75, 0.0});
    assert(t2.isIntersection(&t1));
    std::cout << "planeIntersect3 done\n";
}
// tilted plane 1
void planeIntersect4(){
    rytg::Triangle t1(rytg::Point{0.0, 0.0, 2.0}, rytg::Point{1.0, 3.0, 0.0}, rytg::Point{3.0, 0.0, 3.0});
    rytg::Triangle t2(rytg::Point{2.0, 0.0, 3.0}, rytg::Point{2.0, 3.0, 0.0}, rytg::Point{3.0, 0.0, 3.0});
    assert(!t2.isIntersection(&t1));
    std::cout << "planeIntersect4 done\n";
}
// tilted plane 2
void planeIntersect5(){
    rytg::Triangle t1(rytg::Point{3.0, 3.0, 0.0}, rytg::Point{0.0, 3.0, 3.0}, rytg::Point{0.0, 2.0, 3.0});
    rytg::Triangle t2(rytg::Point{3.0, 0.0, 0.0}, rytg::Point{0.0, 1.0, 3.0}, rytg::Point{0.0, 0.0, 3.0});
    assert(!t2.isIntersection(&t1));
    std::cout << "planeIntersect5 done\n";
}
// tilted plane 3
void planeIntersect6(){
    rytg::Triangle t1(rytg::Point{3.0, 3.0, 0.0}, rytg::Point{0.0, 3.0, 3.0}, rytg::Point{0.0, 1.0, 3.0});
    rytg::Triangle t2(rytg::Point{3.0, 0.0, 0.0}, rytg::Point{0.0, 2.0, 3.0}, rytg::Point{0.0, 0.0, 3.0});
    assert(t2.isIntersection(&t1));
    std::cout << "planeIntersect6 done\n";
}
// tilted plane 4
void planeIntersect7(){
    rytg::Triangle t1(rytg::Point{3.0, 3.0, 0.7}, rytg::Point{0.0, 3.0, 3.0}, rytg::Point{0.0, 1.0, 3.0});
    rytg::Triangle t2(rytg::Point{3.0, 0.0, 0.7}, rytg::Point{0.0, 2.0, 3.0}, rytg::Point{0.0, 0.0, 3.0});
    assert(t2.isIntersection(&t1));
    std::cout << "planeIntersect7 done\n";
}
void test_interception(){
    self();
    normal();
    onePoint();
    notIntersect();
    planeIntersect1();
    planeIntersect2();
    planeIntersect3();
    planeIntersect4();
    planeIntersect5();
    planeIntersect6();
    planeIntersect7();
}

}
