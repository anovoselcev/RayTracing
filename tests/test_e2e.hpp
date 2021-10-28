#ifndef TEST_E2E_HPP
#define TEST_E2E_HPP

#include "scene/bsp_tree.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

namespace test_rytg{

    std::vector<rytg::Triangle> parse_input_file(std::istream& is){
        size_t N = 0;
        is >> N;
        std::vector<rytg::Triangle> trigArray(N);
        double x, y, z;
        for(size_t i = 0; i < N; ++i){
            rytg::Point p1, p2, p3;
            is >> x >> y >> z;
            p1 = {x, y, z};
            is >> x >> y >> z;
            p2 = {x, y, z};
            is >> x >> y >> z;
            p3 = {x, y, z};
            trigArray[i] = rytg::Triangle(p1, p2, p3);
        }
        return trigArray;
    }

    double rand_double(void){
        return ((double)rand()/(double)RAND_MAX)*1000;
    }

    void generate_input_file(std::ostream& os){
        uint32_t N = 100;
        os << N << '\n' << std::endl;
        for (uint32_t i = 0; i < N; ++i){
            os << rand_double() << ' ' << rand_double() << ' ' << rand_double() << std::endl;    //p1
            os << rand_double() << ' ' << rand_double() << ' ' << rand_double() << std::endl;    //p2
            os << rand_double() << ' ' << rand_double() << ' ' << rand_double() << '\n' << std::endl;    //p3
        }
    }

    void generate_output_file(std::ostream& os, std::istream& is, std::vector<rytg::Triangle> trigArray){
        size_t N;
        is.seekg(0);
        is >> N;
        std::vector<bool> intersectArray(N, false);
        os << "Parse OK, trig number:" << N << std::endl;
        for ( uint32_t i = 0; i < N-1; i++ ){
            for ( uint32_t j = i + 1; j < N; j++ ){
                if ( trigArray[i].isIntersection(&(trigArray[j])) ){
                        intersectArray[i] = true;
                        intersectArray[j] = true;
                        os << i << ' ' << j << std::endl;   
                }
            }
        }

        for ( uint32_t i = 0; i < N; ++i ){
            if ( intersectArray[i] )
                os << i << std::endl;
        }
    }
}

#endif
