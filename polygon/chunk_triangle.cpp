#include "chunk_triangle.hpp"
#include "../geo/plane.hpp"
#include "../geo/line.hpp"
#include <stdexcept>

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

    size_t ChunkTriangle::getID() const{
        return id_;
    }

    size_t ChunkTriangle::getParentID() const noexcept{
        return parent_->getID();
    }

    Triangle* ChunkTriangle::getParent() const noexcept{
        return parent_.get();
    }

    Point ChunkTriangle::getPoint(size_t idx) const{
        if(idx >= p_.size()) throw std::out_of_range("");
        return p_[idx];
    }

    size_t ChunkTriangle::getNumPoints() const noexcept{
        return p_.size();
    }

    std::shared_ptr<Triangle> ChunkTriangle::getSharedParent() const noexcept{
        return parent_;
    }

    bool ChunkTriangle::isChunks(const Polygon* lhs, const Polygon* rhs){
        const ChunkTriangle* ch_lhs = dynamic_cast<const ChunkTriangle*>(lhs);
        const ChunkTriangle* ch_rhs = dynamic_cast<const ChunkTriangle*>(rhs);
        if(ch_lhs && ch_rhs && (ch_lhs->getParent() == ch_rhs->getParent())) return true;
        return false;
    }


    bool ChunkTriangle::isChunck(const Polygon* p){
        return dynamic_cast<const ChunkTriangle*>(p) != nullptr;
    }

    std::array<Polygon*, 2> ChunkTriangle::splitChunk(const ChunkTriangle* ct, const Plane& p){
        auto line = p.intersection(ct->getPlane());
        auto t = line.intersection(*ct->getParent(), p);
        std::vector<Point> above{line.getValue(t[0]), line.getValue(t[1])};
        std::vector<Point> below(above);
        for(uint8_t i = 0; i < ct->getNumPoints(); ++i){
            if(p.isAbove(ct->getPoint(i))) above.push_back(ct->getPoint(i));
            if(p.isBelow(ct->getPoint(i))) below.push_back(ct->getPoint(i));
        }
        //TODO
        /*
        auto last = std::unique(above.begin(), above.end());
        above.erase(last, above.end());
        last = std::unique(below.begin(), below.end());
        below.erase(last, below.end());
        */
        return {nullptr, nullptr};
    }
}
