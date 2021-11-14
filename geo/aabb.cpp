#include "geo/aabb.hpp"

#include <cmath>
#include <iostream>


namespace rytg{

Aabb::Aabb(const Triangle& t) noexcept{
    double x_min, y_min, z_min;
    double x_max, y_max, z_max;

    x_min = getMinCoordinate(t.getPoint(0).get(0), t.getPoint(1).get(0), t.getPoint(2).get(0));
    y_min = getMinCoordinate(t.getPoint(0).get(1), t.getPoint(1).get(1), t.getPoint(2).get(1));
    z_min = getMinCoordinate(t.getPoint(0).get(2), t.getPoint(1).get(2), t.getPoint(2).get(2));

    x_max = getMaxCoordinate(t.getPoint(0).get(0), t.getPoint(1).get(0), t.getPoint(2).get(0));
    y_max = getMaxCoordinate(t.getPoint(0).get(1), t.getPoint(1).get(1), t.getPoint(2).get(1));
    z_max = getMaxCoordinate(t.getPoint(0).get(2), t.getPoint(1).get(2), t.getPoint(2).get(2));

    min_ = {x_min, y_min, z_min};
    max_ = {x_max, y_max, z_max};

    //std::cout << "min_:" << min_.get(0) << ' ' <<  min_.get(1) << ' '  <<  min_.get(2) <<'\n';
    //std::cout << "max_:" << max_.get(0) << ' ' << max_.get(1) << ' '  << max_.get(2) <<'\n';

}

double Aabb::getMinCoordinate(const double x1, const double x2, const double x3) const noexcept{
    if ( x1 < x2 && x2 < x3 ){
        return x1;
    } else if ( x2 < x3 ){
        return x2;
    }else{
        return x3;
    }
}

double Aabb::getMaxCoordinate(const double x1, const double x2, const double x3) const noexcept{
    if ( x1 > x2 && x2 > x3 ){
        return x1;
    } else if ( x2 > x3 ){
        return x2;
    }else{
        return x3;
    }
}

bool Aabb::isInBox(const Point& p) const noexcept{

    for (uint8_t i = 0; i < 3; i++){
      if ( Double::eq(min_.get(i), p.get(i)) || Double::eq(max_.get(i), p.get(i)) ) continue; 
      if ( (min_.get(i) > p.get(i)) || (max_.get(i) < p.get(i)) ) return false; 
    }
    return true;
}

bool Aabb::isIntersection(const Aabb& other) const noexcept{

    for (uint8_t i = 0; i < 3; i++){
      if ( Double::eq(max_.get(i), other.min_.get(i)) || Double::eq(min_.get(i), other.max_.get(i)) ) continue; 
      if ( (max_.get(i) < other.min_.get(i) || min_.get(i) > other.max_.get(i)) ) return false; 
    }
    return true;
}

}
