#ifndef POINT_HPP
#define POINT_HPP
#include <limits>

namespace rytg{

    inline double deps = std::numeric_limits<double>::epsilon();

    struct Point{

        double x = 0.0,
               y = 0.0,
               z = 0.0;

        double get(size_t idx) const noexcept;

    };
}

#endif