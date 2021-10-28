#include "geo/line.hpp"
#include <cmath>
#include <algorithm>

namespace rytg{

    Line::Line(const Plane& lhs, const Plane& rhs) noexcept{
        L_ = lhs.getNormal().cross(rhs.getNormal());
        if(L_.isNull()) return;
        double x, y, z;
        Vector3D lhs_N = lhs.getNormal();
        Vector3D rhs_N = rhs.getNormal();
        if (std::fabs(L_.get(0)) > deps){
            x = 0;
            double det = lhs_N.get(1) * rhs_N.get(2) - lhs_N.get(2) * rhs_N.get(1);
            y = (rhs.getConstant() * lhs_N.get(2) - rhs_N.get(2) * lhs.getConstant()) / det;
            z = (lhs.getConstant() * rhs_N.get(1) - lhs_N.get(1) * rhs.getConstant()) / det;
        }
        else if(std::fabs(L_.get(1)) > deps){
            y = 0;
            double det = lhs_N.get(0) * rhs_N.get(2) - lhs_N.get(2) * rhs_N.get(0);
            x = (rhs.getConstant() * lhs_N.get(2) - rhs_N.get(2) * lhs.getConstant()) / det;
            z = (lhs.getConstant() * rhs_N.get(0) - lhs_N.get(0) * rhs.getConstant()) / det;
        }
        else{
            z = 0;
            double det = lhs_N.get(0) * rhs_N.get(1) - lhs_N.get(1) * rhs_N.get(0);
            x = (rhs.getConstant() * lhs_N.get(1) - rhs_N.get(1) * lhs.getConstant()) / det;
            y = (lhs.getConstant() * rhs_N.get(0) - lhs_N.get(0) * rhs.getConstant()) / det;
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

    std::vector<double> Line::intersection(const Triangle& t, const Plane& p) const noexcept{
        Section s[3] = {Section(t.getPoint(0), t.getPoint(1)),
                        Section(t.getPoint(1), t.getPoint(2)),
                        Section(t.getPoint(2), t.getPoint(0))};
        std::vector<double> res;
        for(wint_t i = 0; i < 3; ++i){
            double param = intersection(s[i], s[i].intersection(p));
            if(!std::isnan(param))
                res.push_back(param);
        }
        if(res.size() == 2 && res[0] > res[1]){
            std::swap(res[0], res[1]);
        }
        return res; 
    }

    double Line::intersection(const Section& sec, double s) const noexcept{
        double check = NAN;
        for(wint_t j = 0; j < 3; ++j){
            double tmp = NAN;
            double numer = sec.get(0).get(j) + s * (sec.get(1).get(j) - sec.get(0).get(j)) - P0_.get(j);
            if(std::fabs(L_.get(j)) > deps){
                tmp = numer / L_.get(j);
                if(!std::isnan(check) && std::fabs(tmp - check) > deps) return NAN;
                check = tmp;
            }
            else if(std::fabs(numer) > deps){
                return NAN;
            }
        }
        /*auto it = std::unique(checker.begin(), checker.end(), [](auto lhs, auto rhs){
            return std::fabs(lhs - rhs) <= deps;
        });
        checker.erase(it, checker.end());
        if(checker.size() == 1 && sec.isInSection(getValue(checker[0])))
            return *checker.begin();*/
        if(!std::isnan(check) && sec.isInSection(getValue(check)))
            return check;
        return NAN;
    }
 
}
