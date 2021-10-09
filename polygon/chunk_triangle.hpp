#ifndef CHUNK_TRIANGLE_HPP
#define CHUNK_TRIANGLE_HPP

#include "triangle.hpp"
#include <vector>

namespace rytg{
    class ChunkTriangle : public Polygon{
        
        Triangle* parent_ = nullptr;
        std::vector<Point> p_;

        public:

        ChunkTriangle() = delete;

        ChunkTriangle(Triangle* parent, const std::vector<Point>& points) noexcept;

        bool isIntersection(const Polygon& p) const;

        Plane getPlane() const;

    };
}

#endif