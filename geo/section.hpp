#ifndef SECTION_HPP
#define SECTION_HPP

#include "geo/point.hpp"
#include "geo/plane.hpp"
#include <array>

namespace rytg{
  
    class Section{
      std::array<Point, 2> p_;

      public:

      Section(const Point& p1, const Point& p2) noexcept;

      double intersection(const Plane& p) const noexcept;

      static bool isIntersection(const std::vector<double>& t1,
                                 const std::vector<double>& t2);

      Point get(std::size_t idx) const noexcept;

      bool isInSection(const Point& p) const noexcept;
        
    };
}

#endif 
