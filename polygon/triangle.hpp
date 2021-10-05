#pragma once

#include "../geo/point.hpp"

namespace rytg{

    class Triangle{

        Point p1_,
              p2_,
              p3_;

        public:

        Triangle() = default;

        Triangle(Point p1, Point p2, Point p3);

        Triangle(const Triangle& other) = default;

        Point getPoint(size_t v) const noexcept;

        bool intersection(const Triangle& t) const noexcept;


    };
}