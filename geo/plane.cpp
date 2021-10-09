#include "plane.hpp"
#include "line.hpp"

namespace rytg{

    Plane::Plane(Vector3D N, double d) noexcept : N_(N), d_(d){}

    Plane::Plane(const Polygon& p) noexcept : Plane(p.getPlane()) {}

    Plane::Plane(const Plane& p) noexcept : N_(p.N_), d_(p.d_){}

    Plane::Plane(const Triangle& t) noexcept{
        Vector3D edge1(t.getPoint(1), t.getPoint(0));
        Vector3D edge2(t.getPoint(2), t.getPoint(0));
        N_ = edge1.cross(edge2);
        d_ = - N_.dot(edge1);
    }

    bool Plane::isAbove(const Vector3D& v) const noexcept{
        double value = N_.dot(v) + d_;
        if(value >= 0) return true;
        return false;
    }

    bool Plane::isOnPlane(const Vector3D& v) const noexcept{
        return (N_.dot(v) + d_) == 0;
    }

    bool Plane::isOnPlane(const Triangle& t) const noexcept{
        return isOnPlane(t.getPoint(0)) && isOnPlane(t.getPoint(1)) && isOnPlane(t.getPoint(2));
    }

    bool Plane::isAbove(Point p) const noexcept{
        double value = N_.dot(Vector3D(p)) + d_;
        if(value > 0) return true;
        return false;
    }

    bool Plane::isAbove(const Triangle& t) const noexcept{
        return isAbove(t.getPoint(0)) && isAbove(t.getPoint(1)) && isAbove(t.getPoint(2));
    }

    bool Plane::isBelow(Point p) const noexcept{
        double value = N_.dot(Vector3D(p)) + d_;
        if(value < 0) return true;
        return false;
    }

    bool Plane::isBelow(const Triangle& t) const noexcept{
        return isBelow(t.getPoint(0)) && isBelow(t.getPoint(1)) && isBelow(t.getPoint(2));
    }

    bool Plane::isIntersection(const Triangle& t) const noexcept{
        return !isAbove(t) && !isBelow(t);
    }

    double Plane::distance(Point p) const noexcept{
        return N_.dot(Vector3D(p)) + d_;
    }

    Vector3D Plane::getNormal() const noexcept{
        return N_;
    }

    double Plane::getConstant() const noexcept{
        return d_;
    }

    Line Plane::intersection(const Plane& p) const noexcept{
        return Line(*this, p);
    }


}