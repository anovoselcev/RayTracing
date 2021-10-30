#ifndef TEST_E2E_HPP
#define TEST_E2E_HPP

#include "scene/bsp_tree.hpp"
#include <vector>
#include <ios>
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
        return ((double)rand()/(double)RAND_MAX)*10000;
    }

    void generate_input_file(std::ostream& os){
        uint32_t N = 10;
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
        //os << "Parse OK, trig number:" << N << std::endl;
        for ( uint32_t i = 0; i < N-1; i++ ){
            for ( uint32_t j = i + 1; j < N; j++ ){
                if ( trigArray[i].isIntersection(&(trigArray[j])) ){
                        intersectArray[i] = true;
                        intersectArray[j] = true;
                        //os << i << ' ' << j << std::endl;   
                }
            }
        }

        //os << '\n' << std::endl;

        for ( uint32_t i = 0; i < N; ++i ){
            if ( intersectArray[i] )
                os << i << std::endl;
        }
    }

    void testParseTriangles( rytg::BSPtree bsp, std::istream& is){
    size_t N = 0;
    is >> N;
    double x, y, z;
    for(size_t i = 0; i < N; ++i){
        rytg::Point p1, p2, p3;
        is >> x >> y >> z;
        p1 = {x, y, z};
        is >> x >> y >> z;
        p2 = {x, y, z};
        is >> x >> y >> z;
        p3 = {x, y, z};
        rytg::Triangle* T = new rytg::Triangle(p1, p2, p3);
        bsp.add(T);
    }
}

    void test_file_e2e(std::fstream& randfis,std::fstream& progfos,std::fstream& testresfos){
    std::vector<rytg::Triangle> trigArray;
    rytg::BSPtree bsp(progfos);
    trigArray = test_rytg::parse_input_file(randfis);
    
    test_rytg::generate_output_file(testresfos, randfis, trigArray);
    randfis.seekg(0);
    testParseTriangles(bsp, randfis);
    }

    void test_e2e(void){
        std::fstream randfis1("G:\\validation\\input_rand1.in");
        std::fstream progfos1("G:\\validation\\program_result1.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos1("G:\\validation\\test_result1.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream randfis2("G:\\validation\\input_rand2.in");
        std::fstream progfos2("G:\\validation\\program_result2.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos2("G:\\validation\\test_result2.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream randfis3("G:\\validation\\input_rand3.in");
        std::fstream progfos3("G:\\validation\\program_result3.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos3("G:\\validation\\test_result3.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream randfis4("G:\\validation\\input_rand4.in");
        std::fstream progfos4("G:\\validation\\program_result4.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos4("G:\\validation\\test_result4.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream randfis5("G:\\validation\\input_rand5.in");
        std::fstream progfos5("G:\\validation\\program_result5.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos5("G:\\validation\\test_result5.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream randfis6("G:\\validation\\input_rand6.in");
        std::fstream progfos6("G:\\validation\\program_result6.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos6("G:\\validation\\test_result6.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream randfis7("G:\\validation\\input_rand7.in");
        std::fstream progfos7("G:\\validation\\program_result7.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos7("G:\\validation\\test_result7.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream randfis8("G:\\validation\\input_rand8.in");
        std::fstream progfos8("G:\\validation\\program_result8.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos8("G:\\validation\\test_result8.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream randfis9("G:\\validation\\input_rand9.in");
        std::fstream progfos9("G:\\validation\\program_result9.out", std::ofstream::out | std::ofstream::trunc);
        std::fstream testresfos9("G:\\validation\\test_result9.out", std::ofstream::out | std::ofstream::trunc);

        test_file_e2e(randfis1, progfos1, testresfos1);
        test_file_e2e(randfis2, progfos2, testresfos2);
        test_file_e2e(randfis3, progfos3, testresfos3);
        test_file_e2e(randfis4, progfos4, testresfos4);
        test_file_e2e(randfis5, progfos5, testresfos5);
        test_file_e2e(randfis6, progfos6, testresfos6);
        test_file_e2e(randfis7, progfos7, testresfos7);
        test_file_e2e(randfis8, progfos8, testresfos8);
        test_file_e2e(randfis9, progfos9, testresfos9);

        randfis1.close();
        progfos1.close();
        testresfos1.close();

        randfis2.close();
        progfos2.close();
        testresfos2.close();

        randfis3.close();
        progfos3.close();
        testresfos3.close();

        randfis4.close();
        progfos4.close();
        testresfos4.close();

        randfis4.close();
        progfos4.close();
        testresfos4.close();

        randfis5.close();
        progfos5.close();
        testresfos5.close();

        randfis6.close();
        progfos6.close();
        testresfos6.close();

        randfis7.close();
        progfos7.close();
        testresfos1.close();

        randfis8.close();
        progfos8.close();
        testresfos8.close();

        randfis9.close();
        progfos9.close();
        testresfos9.close();
    }

}

#endif
