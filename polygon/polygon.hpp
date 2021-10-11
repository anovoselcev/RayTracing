#ifndef POLYGON_HPP
#define POLYGON_HPP

namespace rytg{

    class Plane;
    
    class Polygon{
        public:
        virtual bool isIntersection(const Polygon* p) const = 0;

        virtual Plane getPlane() const = 0;

        virtual ~Polygon();
    };

}


#endif
