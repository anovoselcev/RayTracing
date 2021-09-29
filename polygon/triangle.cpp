#include "triangle.hpp"
#include "plane.hpp"
#include "../geo/matrix.hpp"

namespace rytg{

    Triangle::Triangle(Point p1, Point p2, Point p3) : p1_(p1), p2_(p2), p3_(p3) {}

    Point Triangle::getPoint(size_t index) const noexcept{
        switch(index) {
            case 0: return p1_;
            case 1: return p2_;
            case 2: return p3_;
            default: return Point();
        }
    }

    bool Triangle::intersection(const Triangle& t) const noexcept{
        Vector3D p1(t.getPoint(1), t.getPoint(0));
        Vector3D p2(t.getPoint(1), t.getPoint(2));
        Point P(t.getPoint(1));
        Vector3D q1(getPoint(1), getPoint(0));
        Vector3D q2(getPoint(1), getPoint(2));
        Vector3D q3(getPoint(2), getPoint(0));
        Vector3D r1(getPoint(0), P);
        Vector3D r2(getPoint(0), P);
        Vector3D r3(getPoint(0), P);
        Matrix m1(p1, p2, q1);

        return false;
    }

}