#include "chunk_triangle.hpp"
#include "../geo/plane.hpp"

namespace rytg{

    ChunkTriangle::ChunkTriangle(std::shared_ptr<Triangle> parent,
                                 const std::vector<Point>& points) noexcept :
                                 parent_(parent), p_(points){} 

    bool ChunkTriangle::isIntersection(const Polygon* p) const{
        if(!parent_) return false;
        return parent_->isIntersection(p);
    }

    Plane ChunkTriangle::getPlane() const{
        if(parent_) return parent_->getPlane();
        return Plane(Vector3D(), 0.0);
    }

    Triangle* ChunkTriangle::getParent() const noexcept{
        return parent_.get();
    }

    bool ChunkTriangle::isChunks(const Polygon* lhs, const Polygon* rhs){
        const ChunkTriangle* ch_lhs = dynamic_cast<const ChunkTriangle*>(lhs);
        const ChunkTriangle* ch_rhs = dynamic_cast<const ChunkTriangle*>(rhs);
        if(ch_lhs && ch_rhs && (ch_lhs->getParent() == ch_rhs->getParent())) return true;
        return false;
    }
}
