#include "matrix.hpp"

namespace rytg{

    Matrix::Matrix(const Vector3D& v1,
                  const Vector3D& v2,
                  const Vector3D& v3) :  m_({v1, v2, v3}){}

    
    Vector3D Matrix::operator*(const Vector3D& v) const noexcept{
        Vector3D res(m_[0].get(0) * v.get(0) + m_[1].get(0) * v.get(1) + m_[2].get(0) * v.get(2),
                     m_[0].get(1) * v.get(0) + m_[1].get(1) * v.get(1) + m_[2].get(0) * v.get(2),
                     m_[0].get(2) * v.get(0) + m_[1].get(2) * v.get(1) + m_[2].get(2) * v.get(2));

        return res;
    }

    double Matrix::det() const noexcept{
        return m_[0].get(0) * m_[1].get(1) * m_[2].get(2)
               - m_[0].get(0) * m_[1].get(2) * m_[2].get(1)
               - m_[0].get(1) * m_[1].get(0) * m_[2].get(2)
               + m_[0].get(1) * m_[1].get(2) * m_[2].get(0)
               + m_[0].get(2) * m_[1].get(0) * m_[2].get(1)
               - m_[0].get(2) * m_[1].get(1) * m_[2].get(0);
    }

}