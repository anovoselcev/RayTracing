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

    Point Line::getValue(double t) const noexcept{
        return {P0_.x + L_.get(0) * t, P0_.y + L_.get(1) * t, P0_.z + L_.get(2) * t};
    }

    std::array<double, 2> Line::intersection(const Triangle& t, const Plane& p) const noexcept{
        Section s1(t.getPoint(0), t.getPoint(1));
        Section s2(t.getPoint(1), t.getPoint(2));
        Section s3(t.getPoint(2), t.getPoint(0));
        std::array<double, 2> res;
        double inter[3] = {intersection(s1, s1.intersection(p)),
                           intersection(s2, s2.intersection(p)),
                           intersection(s3, s3.intersection(p))};
        size_t not_nan = 0;
        for(uint8_t i = 0, j = 0; i < 3; ++i){
            if(inter[i] == inter[i]){
                not_nan++;
                res[j++] = inter[i];
            }
        }
        if(not_nan != 2) return {NAN, NAN};

        double start = std::min(res[0], res[1]);
        double end   = std::max(res[0], res[1]);
        return {start, end};  
    }

    double Line::intersection(const Section& sec, double s) const noexcept{
        std::map<double, bool> checker;
        for(uint8_t j = 0; j < 3; ++j){
            double tmp = NAN;
            double numer = sec.get(0).get(j) + s * (sec.get(1).get(j) - sec.get(0).get(j)) - P0_.get(j);
            if(std::abs(L_.get(j)) > deps){
                tmp = numer / L_.get(j);
                checker[tmp] = true;
            }
            else if(std::fabs(numer) > deps){
                return NAN;
            }

        }
        if(checker.size() == 1)
            return checker.begin()->first;
        return NAN;
    }
 
}