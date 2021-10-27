#include "geo/vector3d.hpp"
#include <stdexcept>
#include <cmath>

namespace rytg{

        Vector3D::Vector3D(Point end, Point start, bool norm) noexcept{
            direction_.x = end.x - start.x;
            direction_.y = end.y - start.y;
            direction_.z = end.z - start.z;
            if(norm)
                normalize();
        }

        Vector3D::Vector3D(Point end, bool norm) noexcept{
            direction_ = end;
            if(norm)
                normalize();
        }

        Vector3D::Vector3D(double x, double y, double z, bool norm) noexcept{
            direction_.x = x;
            direction_.y = y;
            direction_.z = z;
            if(norm)
                normalize();
        }

        double Vector3D::module() const noexcept{
            double x2 = std::pow(direction_.x, 2);
            double y2 = std::pow(direction_.y, 2);
            double z2 = std::pow(direction_.z, 2);
            return std::sqrt(x2 + y2 + z2);
        }

        void Vector3D::normalize(){
            double m = module();
            if(std::fabs(m) >= deps){
                direction_.x /= m;
                direction_.y /= m;
                direction_.z /= m;
            }
        }

        bool Vector3D::isNull() const noexcept{
            return std::fabs(direction_.x) <= deps &&
                   std::fabs(direction_.y) <= deps &&
                   std::fabs(direction_.z) <= deps;
        }

        double Vector3D::get(std::size_t index) const{
            switch(index) {
                case 0: return direction_.x;
                case 1: return direction_.y;
                case 2: return direction_.z;
                default: throw std::out_of_range("Wrong vector index");
            }
        }

        double Vector3D::dot(const Vector3D& v) const noexcept{
            return v.get(0) * get(0) + v.get(1) * get(1) + v.get(2) * get(2);
        }

        double Vector3D::dot(const Point& p) const noexcept{
            return p.x * get(0) + p.y * get(1) + p.z * get(2);
        }

        Vector3D Vector3D::cross(const Vector3D& v, bool norm) const noexcept{
            double x = get(1) * v.get(2) - get(2) * v.get(1);
            double y = get(2) * v.get(0) - get(0) * v.get(2);
            double z = get(0) * v.get(1) - get(1) * v.get(0);
            return Vector3D(x, y, z, norm);
        }

        Vector3D Vector3D::operator+(const Vector3D& v) const noexcept{
            return Vector3D(get(0) + v.get(0), get(1) + v.get(1), get(2) + v.get(2));
        }

        Vector3D Vector3D::operator-(const Vector3D& v) const noexcept{
            return Vector3D(get(0) - v.get(0), get(1) - v.get(1), get(2) - v.get(2));
        }

        Vector3D& Vector3D::operator+=(const Vector3D& v) noexcept{
            direction_.x += v.get(0);
            direction_.y += v.get(1);
            direction_.z += v.get(2);
            return *this;
        }

        Vector3D& Vector3D::operator-=(const Vector3D& v) noexcept{
            direction_.x -= v.get(0);
            direction_.y -= v.get(1);
            direction_.z -= v.get(2);
            return *this;
        }

        bool Vector3D::operator==(const Vector3D& v) const noexcept{
            return direction_ == v.direction_;
        }

}
