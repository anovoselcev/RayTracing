#include "triangle.hpp"
#include "../geo/plane.hpp"

#include <cmath>
#include <limits>
#include <stdint.h>
#include <array>
#include <unordered_map>
#include <iostream>

namespace rytg{

    Triangle::Triangle(Point p1, Point p2, Point p3) : p1_(p1), p2_(p2), p3_(p3) {}

    Point Triangle::getPoint(size_t index) const noexcept{
        switch(index) {
            case 0: return p1_;
            case 1: return p2_;
            case 2: return p3_;
            default: return Point();
        }
    }

    bool Triangle::intersection(const Triangle& t) const noexcept{
        Plane p1(*this);
        Plane p2(t);
        double dist_1[3];
        uint8_t plus = 0, minus = 0, zero = 0;
        for(uint8_t i = 0; i < 3; i++) {
            dist_1[i] = p2.getNormal().dot(getPoint(i)) + p2.getConstant();
            if(dist_1[i] > std::numeric_limits<double>::epsilon()) plus++;
            else if(dist_1[i] <  - std::numeric_limits<double>::epsilon()) minus++;
            else zero++;
        }
        
        if(plus == 3 || minus == 3) return false;

        if(zero == 3){
            
        }

        Line L = p1.intersection(p2);

        auto found_s = [](double* dist){
            std::array<double, 3> s;
            for(uint8_t i = 0; i < 3; ++i)
                s[i] = - dist[i] / (dist[(i + 1) % 3] - dist[i]);
            return  s;
        };

        std::array<double, 3> s_1 = found_s(dist_1);

        auto find_t = [](const Line& l,
                         const Triangle& t,
                         const std::array<double, 3>& s) -> std::array<double, 2>{
            double tmp[3] = {l.intersection(t.getPoint(0), t.getPoint(1), s[0]),
                            l.intersection(t.getPoint(1), t.getPoint(2), s[1]),
                            l.intersection(t.getPoint(2), t.getPoint(0), s[2])};
            std::array<double, 2> res;
            size_t not_nan = 0;
            for(uint8_t i = 0, j = 0; i < 3; ++i){
                std::cout << tmp[i] << std::endl;
                if(tmp[i] == tmp[i]){
                    not_nan++;
                    res[j++] = tmp[i];
                }
            }
            if(not_nan != 2) return {NAN, NAN};

            double start = std::min(res[0], res[1]);
            double end   = std::max(res[0], res[1]);
            return {start, end};;  
        };

        auto t1 = find_t(L, *this, s_1);

        
        double dist_2[3];
        for(uint8_t i = 0; i < 3; i++) 
            dist_2[i] = p1.getNormal().dot(t.getPoint(i)) + p1.getConstant();
        
        std::array<double, 3> s_2 = found_s(dist_2);
        
        auto t2 = find_t(L, t, s_2);

        if(t1[0] <= t2[0] && t1[1] > t2[0]) return true;
        if(t2[0] <= t1[0] && t2[1] > t1[0]) return true;

        return false;
    }

}