#ifndef TESTS_HPP
#define TESTS_HPP

#include "tests/test_bsp.hpp"
#include "tests/test_interception.hpp"
#include "tests/test_vector.hpp"
#include <iostream>

namespace test_rytg{

void tests_unite(){
    test_vector();
    test_interception();
    test_bsp();
    std::cerr << "Unit tests done\n";
}
#ifdef E2ETEST
#include "tests/test_e2e.hpp"

void test_standalone(){
    test_e2e();
}
#endif
}

#endif
