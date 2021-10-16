#include "..\geo\vector3d.hpp"
#include <cassert>
#include <cmath>

namespace rytg_test{

    void test_dot(){
        rytg::Vector3D v1(1, 0, 0);
        rytg::Vector3D v2(0, 1, 0);
        assert(std::fabs(v1.dot(v2)) < deps);
        rytg::Vector3D v3(1, 1, 1);
        assert(std::fabs(v1.dot(v3) - 1) < deps);
        assert(std::fabs(v2.dot(v3)) < deps);
    }

    void test_cross(){
        rytg::Vector3D v1(1, 0, 0);
        rytg::Vector3D v2(0, 1, 0);
        assert(v1.cross(v2) == rytg::Vector3D(0, 0, -1));
    }

    void test_vector(){
        test_dot();

    }

}