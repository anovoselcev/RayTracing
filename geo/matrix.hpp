#pragma once
#include "vector3d.hpp"

namespace rytg{

    class Matrix{
        Vector3D m_[3];

        public:

        Matrix() = default;

        Matrix(const Vector3D& v1,
               const Vector3D& v2,
               const Vector3D& v3);

        
        Vector3D operator*(const Vector3D& v) const noexcept;

        double det() const noexcept;
    };

}