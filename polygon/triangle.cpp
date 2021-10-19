#include "triangle.hpp"
#include "chunk_triangle.hpp"
#include "vector3d.hpp"
#include "../geo/plane.hpp"
#include "../geo/line.hpp"

#include <cmath>
#include <algorithm>

namespace rytg{

    Triangle::Triangle(Point p1, Point p2, Point p3) : p_({p1, p2, p3}) {}

    Point Triangle::getPoint(size_t index) const noexcept{
        switch(index) {
            case 0: return p_[0];
            case 1: return p_[1];
            case 2: return p_[2];
            default: return Point();
        }
    }

    Plane Triangle::getPlane() const {
        return Plane(*this);
    }

    bool Triangle::isIntersection(const Polygon* p) const{
        if(const Triangle* t = dynamic_cast<const Triangle*>(p))
            return t->isIntersection(this);
        else if(const ChunkTriangle* ch = dynamic_cast<const ChunkTriangle*>(p))
            return ch->isIntersection(this);
        return false;
    }

    // https://blackpawn.com/texts/pointinpoly/
    bool Triangle::pointInTriangle( const Triangle* t, const Vector3D& p ) const noexcept
    {
        const Vector3D& a1 = Vector3D( t->getPoint(0) ) - Vector3D( t->getPoint(2) );
        const Vector3D& b1 = Vector3D( t->getPoint(1) ) - Vector3D( t->getPoint(2) );
        const float     aa = a1.dot(a1);
        const float	    ab = a1.dot(b1);
        const float     bb = b1.dot(b1);
        const float	d  = aa*bb - ab*ab;

        if ( fabs ( d ) < EPS )
            return false;
      
        const Vector3D& p1 = p - Vector3D( t->getPoint(2) );
        const float     pa = p1.dot(a1);
        const float	    pb = p1.dot(b1);
        const float     u  = (pa*bb - pb*ab) / d;

        if ( u < 0 || u > 1 )
            return false;

        const float v = (pb*aa - pa*ab) / d;

        if ( v < 0 || v > 1 )
            return false;

        return u + v <= 1; 
    }

    bool Triangle::isIntersection(const Triangle* t) const noexcept{
        Plane p1(*this);
        Plane p2(*t);
  
        if(!p2.isIntersection(*this)) return false;
        
        if(p2.isOnPlane(*this)){

            //std::cout << "On plane\n";
            for (int i = 0; i < 3; i++){
                // Если хотя бы одна точка второго треугольника внутри первого, значит есть пересечение треуг-ов
                if ( pointInTriangle( this, Vector3D(t->getPoint(i)) ) )
                    return true;
                if ( pointInTriangle( t, Vector3D(this->getPoint(i)) ) )
                    return true; 
            };

            return false;
        }
        Line L = p1.intersection(p2);

        auto t1 = L.intersection(*this, p2);
        auto t2 = L.intersection(*t, p1);
        
        if (t1.size() == 1 && t2.size() == 1)
            return t1[0] == t2[0];

        if (t1.size() == 1 && t2.size() == 2)
            if(t1[0] >= t2[0] && t1[0] <= t2[1]) return true;
        
        if (t1.size() == 2 && t2.size() == 1)
            if(t2[0] >= t1[0] && t2[0] <= t1[1]) return true;

        if (t1.size() == 2 && t2.size() == 2){
            if(t1[0] <= t2[0] && t1[1] >= t2[0]) return true;
            if(t2[0] <= t1[0] && t2[1] >= t1[0]) return true;
        }

        return false;
    }

    std::array<Polygon*, 2> Triangle::splitToChunks(Triangle* trig, const Plane& p){
        auto line = p.intersection(trig->getPlane());
        auto t = line.intersection(*trig, p);
        std::vector<Point> above{line.getValue(t[0]), line.getValue(t[1])};
        std::vector<Point> below(above);
        for(uint8_t i = 0; i < 3; ++i){
            if(p.isAbove(trig->getPoint(i))) above.push_back(trig->getPoint(i));
            if(p.isBelow(trig->getPoint(i))) below.push_back(trig->getPoint(i));
        }
        auto last = std::unique(above.begin(), above.end());
        above.erase(last, above.end());
        last = std::unique(below.begin(), below.end());
        below.erase(last, below.end());
        if(above.size() <= 2) return {trig, nullptr};
        if(below.size() <= 2) return {nullptr, trig};
        auto trig_shared = std::make_shared<Triangle>(*trig);
        delete trig;
        Polygon* above_chunk = new ChunkTriangle(trig_shared, above);
        Polygon* below_chunk = new ChunkTriangle(trig_shared, below);
        return {below_chunk, above_chunk};
    }

    Triangle* Triangle::mergeChunks(const Polygon* lhs, const Polygon* rhs){
        if(ChunkTriangle::isChunks(lhs, rhs)){

            Triangle* par = new Triangle(*dynamic_cast<const ChunkTriangle*>(lhs)->getParent());
            delete lhs;
            delete rhs;
            return par;
        }
        return nullptr;
    }

    bool Triangle::isTriangle(const Polygon* p){
        return dynamic_cast<const Triangle*>(p) != nullptr;
    }

}
