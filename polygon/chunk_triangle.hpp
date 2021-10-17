#ifndef CHUNK_TRIANGLE_HPP
#define CHUNK_TRIANGLE_HPP

#include "triangle.hpp"
#include <memory>
#include <vector>

namespace rytg{
    class ChunkTriangle : public Polygon{
        
        std::shared_ptr<Triangle> parent_ = nullptr;
        std::vector<Point> p_;

        public:

        ChunkTriangle() = delete;

        ~ChunkTriangle() = default;

        ChunkTriangle(std::shared_ptr<Triangle> parent, const std::vector<Point>& points) noexcept;

        bool isIntersection(const Polygon* p) const;

        Plane getPlane() const;

        Triangle* getParent() const noexcept;

        Point getPoint(size_t idx) const;

        size_t getNumPoints() const noexcept;

        std::shared_ptr<Triangle> getSharedParent() const noexcept;

        static bool isChunks(const Polygon* lhs, const Polygon* rhs);

        static bool isChunck(const Polygon* p);

        static std::array<Polygon*, 2> splitChunk(const ChunkTriangle* ct, const Plane& p);
    };
}

#endif
