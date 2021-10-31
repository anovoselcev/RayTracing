#include "geo/point.hpp"
#include <cmath>
#include <sstream>

namespace rytg{

    double Point::get(std::size_t idx) const noexcept{
        switch(idx){
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return NAN;
        };
    }

    bool Point::operator==(const Point& p) const noexcept{
        return std::fabs(x - p.x) <= deps &&
               std::fabs(y - p.y) <= deps &&
               std::fabs(z - p.z) <= deps;
    }

}
