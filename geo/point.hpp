#pragma once
#include <string>

namespace rytg{

    struct Point{

        double x = 0.0,
               y = 0.0,
               z = 0.0;

        double get(size_t idx) const noexcept;

        std::string to_string() const noexcept;

    };

}