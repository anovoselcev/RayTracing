#ifndef LINE_HPP
#define LINE_HPP

#include "vector3d.hpp"

namespace rytg{

    class Plane;

    class Line{
        Point P0_;
        Vector3D L_;

        public:

        Line(const Plane& lhs, const Plane& rhs) noexcept;

        Vector3D getDirection() const noexcept;

        Point getConstant() const noexcept;

        double intersection(const Point& lhs, const Point& rhs, double s) const noexcept;

    };

}
#endif