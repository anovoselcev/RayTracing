#include "geo/aabb.hpp"

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

double Aabb::getMinCoordinate(const double x1, const double x2, const double x3) noexcept{
    if ( x1 < x2 && x2 < x3 ){
        return x1;
    } else if ( x2 < x3 ){
        return x2;
    }else{
        return x3;
    }
}

double Aabb::getMaxCoordinate(const double x1, const double x2, const double x3) noexcept{
    if ( x1 > x2 && x2 > x3 ){
        return x1;
    } else if ( x2 > x3 ){
        return x2;
    }else{
        return x3;
    }
}

bool Aabb::isIntersection(const Aabb& other) noexcept{

    if (this->max_.get(0) < other.min_.get(0) || this->min_.get(0) > other.max_.get(0)) return false;
    if (this->max_.get(1) < other.min_.get(1) || this->min_.get(1) > other.max_.get(1)) return false;
    if (this->max_.get(2) < other.min_.get(2) || this->min_.get(2) > other.max_.get(2)) return false;
    return true;
}

bool Aabb::isInBox(const Point& p) noexcept{
    if (this->min_.get(0) > p.get(0) || this->max_.get(0) < p.get(0)) return false;
    if (this->min_.get(1) > p.get(1) || this->max_.get(1) < p.get(1)) return false;
    if (this->min_.get(2) > p.get(2) || this->max_.get(2) < p.get(2)) return false;
    return true;
}

}
