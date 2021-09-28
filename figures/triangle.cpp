#include "triangle.hpp"
#include "plane.hpp"

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

}