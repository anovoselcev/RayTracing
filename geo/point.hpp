#ifndef POINT_HPP
#define POINT_HPP
#include <cstddef>
namespace rytg{

    inline double deps = 1e-6;

    struct Point{

        double x = 0.0,
               y = 0.0,
               z = 0.0;

        bool operator==(const Point& p) const noexcept;

        double get(std::size_t idx) const noexcept;

    };
}

#endif
