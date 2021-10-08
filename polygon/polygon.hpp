#ifndef POLYGON_HPP
#define POLYGON_HPP

namespace rytg{

    class Polygon{
        public:
        virtual bool isIntersection(const Polygon& p) const = 0;
    };

}


#endif