#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "point.hpp"

namespace rytg{

    class Vector3D{

        Point direction_;

        public:

        Vector3D() = default;

        Vector3D(Point end, Point start = Point()) noexcept;

        Vector3D(double x, double y, double z) noexcept;

        bool isNull() const noexcept;

        double get(std::size_t idx) const;

        // Скалярное произведение
        double dot(const Vector3D& v) const noexcept;
        // Векторное произведение
        Vector3D cross(const Vector3D& v) const noexcept;

        Vector3D operator+(const Vector3D& v) const noexcept;

        Vector3D operator-(const Vector3D& v) const noexcept;

        Vector3D& operator+=(const Vector3D& v) noexcept;

        Vector3D& operator-=(const Vector3D& v) noexcept;

    };
}

#endif