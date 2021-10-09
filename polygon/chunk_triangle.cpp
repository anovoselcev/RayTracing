#include "chunk_triangle.hpp"
#include "../geo/plane.hpp"

namespace rytg{

    ChunkTriangle::ChunkTriangle(Triangle* parent,
                                 const std::vector<Point>& points) noexcept :
                                 parent_(parent), p_(points){} 

    bool ChunkTriangle::isIntersection(const Polygon& p) const{
        if(!parent_) return false;
        return parent_->isIntersection(p);
    }

    Plane ChunkTriangle::getPlane() const{
        if(parent_) return parent_->getPlane();
    }
}