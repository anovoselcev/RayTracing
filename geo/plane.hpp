#pragma once
#include "../geo/vector3d.hpp"
#include "../geo/line.hpp"
#include "../polygon/triangle.hpp"

namespace rytg{

    class Plane{

        Vector3D N_;
        double d_ = 0.0;

        public:

        Plane(const Triangle& t) noexcept;

        Plane(Vector3D N, double d = 0) noexcept;

        bool isAbove(const Vector3D& v) const noexcept;

        bool isOnPlane(const Vector3D& v) const noexcept;

        bool isAbove(Point p) const noexcept;

        bool isAbove(const Triangle& t) const noexcept;

        bool isOnPlane(Point p) const noexcept;

        Vector3D getNormal() const noexcept;

        double getConstant() const noexcept;

        Line intersection(const Plane& p) const noexcept;

    };
}