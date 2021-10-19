#ifndef POLYGON_HPP
#define POLYGON_HPP

namespace rytg{

class Plane;

class Polygon{

    static size_t ID;

protected:

    size_t id_ = 0;

public:

    Polygon();

    virtual bool isIntersection(const Polygon* p) const = 0;

    virtual Plane getPlane() const = 0;

    virtual size_t getID() const = 0;

    virtual ~Polygon();
};

}


#endif
