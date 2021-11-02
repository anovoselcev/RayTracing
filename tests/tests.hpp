#ifndef TESTS_HPP
#define TESTS_HPP

#include "tests/test_bsp.hpp"
#include "tests/test_e2e.hpp"
#include "tests/test_interception.hpp"
#include "tests/test_vector.hpp"

namespace test_rytg{
void tests(){
    test_vector();
    test_interception();
    test_bsp();
}
}

#endif
