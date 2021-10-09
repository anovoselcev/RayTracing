#include "triangle.hpp"
#include "../geo/plane.hpp"
#include "../geo/line.hpp"
#include <iostream>

namespace rytg{

    Triangle::Triangle(Point p1, Point p2, Point p3) : p_({p1, p2, p3}) {}

    Point Triangle::getPoint(size_t index) const noexcept{
        switch(index) {
            case 0: return p_[0];
            case 1: return p_[1];
            case 2: return p_[2];
            default: return Point();
        }
    }

    Plane Triangle::getPlane() const {
        return Plane(*this);
    }

    bool Triangle::isIntersection(const Polygon& p) const{
        return p.isIntersection(*this);
    }

    bool Triangle::isIntersection(const Triangle& t) const noexcept{
        Plane p1(*this);
        Plane p2(t);

        if(!p2.isIntersection(*this)) return false;
        
        if(p2.isOnPlane(*this)){
            std::cout << "On plane\n";
        }
        Line L = p1.intersection(p2);

        auto t1 = L.intersection(*this, p2);
        auto t2 = L.intersection(t, p1);

        if(t1[0] <= t2[0] && t1[1] > t2[0]) return true;
        if(t2[0] <= t1[0] && t2[1] > t1[0]) return true;

        return false;
    }

}