#ifndef POLYGON_HPP
#define POLYGON_HPP

namespace rytg{
    template<typename Object>
    class Polygon{
        public:

        template<typename Other>
        bool isIntersection(const Other& oth){
            return static_cast<Object*>(this)->isIntersectionImpl(oth);
        }
    };

}


#endif