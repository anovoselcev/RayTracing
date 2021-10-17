#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "polygon.hpp"
#include "../geo/point.hpp"
#include <array>

namespace rytg{

    class Triangle : public Polygon{

        std::array<Point, 3> p_;

        private:

        inline double Det2D(Point &p1, Point &p2, Point &p3);

        void CheckTriWinding(Point &p1, Point &p2, Point &p3);

        bool BoundaryCollideChk(Point &p1, Point &p2, Point &p3, double eps);

        bool BoundaryDoesntCollideChk(Point &p1, Point &p2, Point &p3, double eps);

        bool TriTri2D(const Triangle *t1, const Triangle *t2, double eps = 0.0, bool onBoundary  = true);

        public:

        Triangle() = default;

        ~Triangle() = default;

        Triangle(Point p1, Point p2, Point p3);

        Triangle(const Triangle& other) = default;

        Point getPoint(std::size_t v) const noexcept;

        bool isIntersection(const Triangle* other) const noexcept;

        bool isIntersection(const Polygon* p) const override;

        Plane getPlane() const override;

        static std::array<Polygon*, 2> splitToChunks(Triangle* t, const Plane& p);

        static Triangle* mergeChunks(const Polygon* lhs, const Polygon* rhs);

    };
}

#endif
