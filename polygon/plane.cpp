#include "triangle.hpp"
#include "plane.hpp"

namespace rytg{

    Plane::Plane(Vector3D N, double d) : N_(N), d_(d){}

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

    bool Plane::isAbove(Point p) const noexcept{
        double value = N_.dot(Vector3D(p)) + d_;
        if(value >= 0) return true;
        return false;
    }

    bool Plane::isOnPlane(Point p) const noexcept{
        return (N_.dot(Vector3D(p)) + d_) == 0;
    }

    Vector3D Plane::getNormal() const noexcept{
        return N_;
    }

    double Plane::getConstant() const noexcept{
        return d_;
    }


}