#include "line.hpp"
#include "plane.hpp"
#include <limits>
#include <cmath>
#include <map>

namespace rytg{

    Line::Line(const Plane& lhs, const Plane& rhs) noexcept{
        L_ = lhs.getNormal().cross(rhs.getNormal());
        if(L_.isNull()) return;
        double x, y, z;
        Vector3D lhs_N = lhs.getNormal();
        Vector3D rhs_N = rhs.getNormal();
        if (L_.get(0) != 0){
            x = 0;
            double det = lhs_N.get(1) * rhs_N.get(2) - lhs_N.get(2) * rhs_N.get(1);
            y = (rhs.getConstant() * lhs_N.get(2) - rhs_N.get(2) * lhs.getConstant()) / det;
            z = (lhs.getConstant() * rhs_N.get(1) - rhs_N.get(1) * lhs.getConstant()) / det;
        }
        else if(L_.get(1) != 0){
            y = 0;
            double det = lhs_N.get(0) * rhs_N.get(2) - lhs_N.get(2) * rhs_N.get(0);
            x = (rhs.getConstant() * lhs_N.get(2) - rhs_N.get(2) * lhs.getConstant()) / det;
            z = (lhs.getConstant() * rhs_N.get(0) - rhs_N.get(0) * lhs.getConstant()) / det;
        }
        else{
            z = 0;
            double det = lhs_N.get(0) * rhs_N.get(1) - lhs_N.get(1) * rhs_N.get(0);
            x = (rhs.getConstant() * lhs_N.get(1) - rhs_N.get(1) * lhs.getConstant()) / det;
            z = (lhs.getConstant() * rhs_N.get(0) - rhs_N.get(0) * lhs.getConstant()) / det;
        }
        P0_ = {x, y, z};
    }

    Vector3D Line::getDirection() const noexcept{
        return L_;
    }

    Point Line::getConstant() const noexcept{
        return P0_;
    }

    double Line::intersection(const Point& lhs, const Point& rhs, double s) const noexcept{
        std::map<double, bool> checker;
        for(uint8_t j = 0; j < 3; ++j){
            double tmp = NAN;
            if(std::abs(L_.get(j)) > std::numeric_limits<double>::epsilon()){
                tmp = (lhs.get(j) + s * (rhs.get(j) - lhs.get(j)) - P0_.get(j)) / L_.get(j);
                checker[tmp] = true;
            }
            else if(std::fabs(lhs.get(j) + s * (rhs.get(j) - lhs.get(j)) - P0_.get(j)) > std::numeric_limits<double>::epsilon()){
                return NAN;
            }

        }
        if(checker.size() == 1)
            return checker.begin()->first;
        return NAN;
    }
 
}