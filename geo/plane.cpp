#include "plane.hpp"
#include "line.hpp"
#include "../polygon/chunk_triangle.hpp"
#include <cmath>

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

    bool Plane::operator==(const Plane& p) const noexcept{
        return N_.cross(p.N_).isNull() && std::fabs(d_) == std::fabs(p.d_);
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

    bool Plane::isOnPlane(const Polygon& p) const noexcept{
        if(const Triangle* t = dynamic_cast<const Triangle*>(&p))
            return isOnPlane(*t);
        else if(const ChunkTriangle* ct = dynamic_cast<const ChunkTriangle*>(&p))
            return isOnPlane(*(ct->getParent()));
        return false;
    }

    bool Plane::isAbove(Point p) const noexcept{
        double value = N_.dot(Vector3D(p)) + d_;
        if(value > 0) return true;
        return false;
    }

    bool Plane::isAbove(const Triangle& t) const noexcept{
        return isAbove(t.getPoint(0)) && isAbove(t.getPoint(1)) && isAbove(t.getPoint(2));
    }

    bool Plane::isAbove(const Polygon& p) const noexcept{
        if(const Triangle* t = dynamic_cast<const Triangle*>(&p))
            return isAbove(*t);
        else if(const ChunkTriangle* ct = dynamic_cast<const ChunkTriangle*>(&p))
            return isAbove(*ct);
        return false;
    }

    bool Plane::isBelow(Point p) const noexcept{
        // Не особо понял, что именно происходит
        double value = N_.dot(Vector3D(p)) + d_;
        if(value < 0) return true;
        return false;
    }

    bool Plane::isBelow(const Triangle& t) const noexcept{
        return isBelow(t.getPoint(0)) && isBelow(t.getPoint(1)) && isBelow(t.getPoint(2));
    }

    bool Plane::isBelow(const Polygon& p) const noexcept{
        if(const Triangle* t = dynamic_cast<const Triangle*>(&p))
            return isBelow(*t);
        else if(const ChunkTriangle* ct = dynamic_cast<const ChunkTriangle*>(&p))
            return isBelow(*ct);
        return false;
    }

    bool Plane::isIntersection(const Triangle& t) const noexcept{
        return !isAbove(t) && !isBelow(t);
    }

    bool Plane::isIntersection(const Polygon& p) const noexcept{
        if(const Triangle* t = dynamic_cast<const Triangle*>(&p))
            return isIntersection(*t);
        else if(const ChunkTriangle* ct = dynamic_cast<const ChunkTriangle*>(&p))
            return isIntersection(*ct);
        return false;
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