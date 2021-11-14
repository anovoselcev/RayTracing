/**
 * @brief Axis-Aligned Bounding Box based on min and max coordinates along each axis
 * 
 */

#ifndef AABB_HPP
#define AABB_HPP

#include "polygon/triangle.hpp"
#include "geo/point.hpp"

#include <vector>

namespace rytg{

    class Aabb{

        Point min_;
        Point max_;

        double getMinCoordinate(const double x1, const double x2, const double x3) const noexcept;

        double getMaxCoordinate(const double x1, const double x2, const double x3) const noexcept;

        public:

        Aabb(const Triangle& t) noexcept;

        bool Aabb::isInBox(const Point& p) const noexcept;

        bool isIntersection(const Aabb& other) const noexcept;
        
    };

}

#endif