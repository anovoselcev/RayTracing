#include "geo/vector3d.hpp"
#include <cassert>
#include <cmath>

namespace test_rytg{

    void test_dot(){
        rytg::Vector3D v1(1, 0, 0);
        rytg::Vector3D v2(0, 1, 0);
        assert(std::fabs(v1.dot(v2)) < rytg::deps);
        rytg::Vector3D v3(1, 1, 1, false);
        std::cout << (std::fabs(v1.dot(v3))) << std::endl;
        std::cout << (std::fabs(v2.dot(v3))) << std::endl;
        assert(std::fabs(v1.dot(v3) - 1) < rytg::deps);
        assert(std::fabs(v2.dot(v3) - 1) < rytg::deps);
    }

    void test_cross(){
        rytg::Vector3D v1(1, 0, 0);
        rytg::Vector3D v2(0, 1, 0);
        assert(v1.cross(v2) == rytg::Vector3D(0, 0, 1));
    }

    void test_vector(){
        test_dot();
        test_cross();
    }

}
