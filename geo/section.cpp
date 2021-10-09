#include "section.hpp"
#include <cmath>

namespace rytg{

    Section::Section(const Point& p1, const Point& p2) noexcept : p_({p1, p2}){}

    double Section::intersection(const Plane& p) const noexcept {
        double d_u0 = p.distance(p_[0]);
        double d_u1 = p.distance(p_[1]);
        if(std::fabs(d_u1 - d_u0) < deps) return NAN;
        double s = - d_u0 / (d_u1 - d_u0);
        return s;
    }

    Point Section::get(size_t idx) const noexcept{
        switch(idx){
            case 0: return p_[0];
            case 1: return p_[1];
            default: return Point{};
        }
    }

}