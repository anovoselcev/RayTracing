#include "triangle.hpp"
#include "chunk_triangle.hpp"
#include "../geo/plane.hpp"
#include "../geo/line.hpp"
#include <iostream>

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

    /**
     * \note Функция для проверки расположения точки, относительно вектора-отрезка. 
     *       Метод основан на псевдоскалярном произведении. В объеме аналогом
     *       псевдоскалярного произведения будем считать векторное произведение.
     * 
     *      https://habr.com/ru/post/148325/
    */
    inline double Triangle::Det2D(Point &p1, Point &p2, Point &p3){
        Vector3D vector1(p2, p1);
        Vector3D vector2(p3, p1);
        Vector3D crossVector = vector1.cross(vector2);

       //std::cout << "destination x = " << crossVector.get(0)  << std::endl;
       //std::cout << "destination y = " << crossVector.get(1)  << std::endl;
       //std::cout << "destination z = " << crossVector.get(2)  << std::endl;
       //Triangle trig(p1, p2, p3);
       //Plane refPlane(trig);

        return crossVector.get(0) +  crossVector.get(1) + crossVector.get(2);
       
    }

    void Triangle::CheckTriWinding(Point &p1, Point &p2, Point &p3){
        double detTri = Det2D(p1, p2, p3);
        if(detTri < 0.0)
        {
                Point a = p3;
                p3 = p2;
                p2 = a;
        };
    }

    bool Triangle::BoundaryCollideChk(Point &p1, Point &p2, Point &p3, double eps){
        return Det2D(p1, p2, p3) < eps;
    }

    bool Triangle::BoundaryDoesntCollideChk(Point &p1, Point &p2, Point &p3, double eps){
        return Det2D(p1, p2, p3) <= eps;;
    }

    bool Triangle::TriTri2D(const Triangle* t1, const Triangle* t2, double eps, bool onBoundary){
        // Подумать, как избежать этого копирования
        Point p1t1 = t1->getPoint(0);
        Point p2t1 = t1->getPoint(1);
        Point p3t1 = t1->getPoint(2);

        Point p1t2 = t2->getPoint(0);
        Point p2t2 = t2->getPoint(1);
        Point p3t2 = t2->getPoint(2);

        //Trangles must be expressed anti-clockwise
	    CheckTriWinding(p1t1, p2t1, p3t1);
	    CheckTriWinding(p1t2, p2t2, p3t2);

        Triangle trig1(p1t1, p2t1, p3t1);
        Triangle trig2(p1t2, p2t2, p3t2);
        /*
        bool (Triangle::* chkEdge)(Point &, Point &, Point &, double) = nullptr;
        if(onBoundary) //Points on the boundary are considered as colliding
            chkEdge = BoundaryCollideChk;
        else //Points on the boundary are not considered as colliding
            chkEdge = BoundaryDoesntCollideChk;
        */
        //For edge E of trangle 1,
        for(int i=0; i<3; i++)
        {
            int j=(i+1)%3;

            Point pit1 = trig1.getPoint(i);
            Point pjt1 = trig1.getPoint(j);

            //Check all points of trangle 2 lay on the external side of the edge E. If
            //they do, the triangles do not collide.
            if (BoundaryCollideChk(pit1, pjt1, p1t2, eps) &&
                BoundaryCollideChk(pit1, pjt1, p2t2, eps) &&
                BoundaryCollideChk(pit1, pjt1, p3t2, eps))
                return false;
        }
    
        //For edge E of trangle 2,
        for(int i=0; i<3; i++)
        {
            int j=(i+1)%3;

            Point pit2 = trig2.getPoint(i);
            Point pjt2 = trig2.getPoint(j);
    
            //Check all points of trangle 1 lay on the external side of the edge E. If
            //they do, the triangles do not collide.
            if (BoundaryCollideChk(pit2, pjt2, p1t1, eps) &&
                BoundaryCollideChk(pit2, pjt2, p2t1, eps) &&
                BoundaryCollideChk(pit2, pjt2, p3t1, eps))
                return false;
        }
    
        //The triangles collide
        return true;
    }

    bool Triangle::isIntersection(const Triangle* t) const noexcept{
        Plane p1(*this);
        Plane p2(*t);
        Triangle trig(*this);

        if(!p2.isIntersection(*this)) return false;
        
        if(p2.isOnPlane(*this)){

            //std::cout << "On plane\n";
            return trig.TriTri2D( this, t, 0.0);
        
        }
        Line L = p1.intersection(p2);

        auto t1 = L.intersection(*this, p2);
        auto t2 = L.intersection(*t, p1);

        if(t1[0] <= t2[0] && t1[1] > t2[0]) return true;
        if(t2[0] <= t1[0] && t2[1] > t1[0]) return true;

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

            Triangle* par = dynamic_cast<const ChunkTriangle*>(lhs)->getParent();
            delete lhs;
            delete rhs;
            return par;
        }
        return nullptr;
    }

}
