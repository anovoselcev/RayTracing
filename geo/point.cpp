#include "point.hpp"
#include <cmath>
#include <sstream>

namespace rytg{

    double Point::get(size_t idx) const noexcept{
        switch(idx){
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return NAN;
        };
    }

    std::string Point::to_string() const noexcept{
        std::stringstream ss;
        ss << "(" << x << "," << y << "," << z << ")";
        return ss.str();
    }

}