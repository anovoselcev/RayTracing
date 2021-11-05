#include "geo/point.hpp"
#include <cmath>
#include <sstream>

namespace rytg{

namespace Double {

    bool eq(double lhs, double rhs){
        return std::fabs(lhs - rhs) < deps;
    }

    bool isNull(double lhs){
        return std::fabs(lhs) < deps;
    }
}

    double Point::get(std::size_t idx) const noexcept{
        switch(idx){
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return NAN;
        };
    }

    bool Point::operator==(const Point& p) const noexcept{
        return Double::eq(x, p.x) &&
               Double::eq(y, p.y) &&
               Double::eq(z, p.z);
    }

}
