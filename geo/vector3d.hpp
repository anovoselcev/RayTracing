#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "geo/point.hpp"

namespace rytg{

    class Vector3D{

        Point direction_;

        public:

        Vector3D() = default;

        Vector3D(Point end, bool norm = true) noexcept;

        Vector3D(Point end, Point start, bool norm = true) noexcept;

        Vector3D(double x, double y, double z, bool normalize = true) noexcept;

        bool isNull() const noexcept;

        double get(std::size_t idx) const;

        double dot(const Vector3D& v) const noexcept;

        double dot(const Point& p) const noexcept;

        double module() const noexcept;

        Vector3D cross(const Vector3D& v, bool norm = true) const noexcept;

        Vector3D operator+(const Vector3D& v) const noexcept;

        Vector3D operator-(const Vector3D& v) const noexcept;

        Vector3D& operator+=(const Vector3D& v) noexcept;

        Vector3D& operator-=(const Vector3D& v) noexcept;

        bool operator==(const Vector3D& v) const noexcept;

        void normalize();
    };
}

#endif
