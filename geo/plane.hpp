#ifndef PLANE_HPP
#define PLANE_HPP

//#include "line.hpp"
#include "vector3d.hpp"
#include "../polygon/triangle.hpp"

namespace rytg{

    class Line;

    class Plane{

        Vector3D N_;
        double d_ = 0.0;

        public:

        Plane(const Triangle& t) noexcept;

        Plane(const Polygon& p) noexcept;

        Plane(const Plane& p) noexcept;

        Plane(Vector3D N, double d = 0) noexcept;

        bool isAbove(const Vector3D& v) const noexcept;

        bool isOnPlane(const Vector3D& v) const noexcept;

        bool isOnPlane(const Triangle& v) const noexcept;

        bool isAbove(Point p) const noexcept;

        bool isAbove(const Triangle& t) const noexcept;

        bool isBelow(Point p) const noexcept;

        bool isBelow(const Triangle& t) const noexcept;

        bool isIntersection(const Triangle& t) const noexcept;

        double distance(Point p) const noexcept;

        Vector3D getNormal() const noexcept;

        double getConstant() const noexcept;

        Line intersection(const Plane& p) const noexcept;

    };
}

#endif