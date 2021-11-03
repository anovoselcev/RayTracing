#ifndef TEST_E2E_HPP
#define TEST_E2E_HPP

#include "scene/bsp_tree.hpp"
#include <vector>
#include <ios>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cassert>

namespace test_rytg{


    double rand_double(){
        return ((double)rand()/(double)RAND_MAX)*10000;
    }

    void testParseTriangles(rytg::BSPtree &bsp, std::istream& is){
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

    void test_file_e2e(std::fstream& randfis, std::fstream& progfos){
        std::vector<rytg::Triangle> trigArray;
        rytg::BSPtree bsp(progfos);

        randfis.seekg(0);
        testParseTriangles(bsp, randfis);
    }

    bool compare_files(std::fstream& manualCheck, std::fstream& progRes){
        uint32_t mcVal = 0, prVal = 0;
        bool eof1 = false, eof2 = false;

        while( !( (eof1 = manualCheck.eof()) || (eof2 =progRes.eof()) ) ){
            manualCheck >> mcVal;
            progRes >> prVal;
            //std::cout << mcVal << ' ' << prVal << std::endl;
            if ( mcVal != prVal )
                return false;
            eof1 = manualCheck.eof();
            eof2 = progRes.eof();
        }

        if (eof1 && eof2)
            return true;
        else
            return false;
    }

    void test_e2e(){
        std::fstream mancheck1("..\\..\\tests\\validation\\manual_check1.txt");
        std::fstream randfis1("..\\..\\tests\\validation\\input_rand1.in");
        std::fstream progfos1("..\\..\\tests\\validation\\program_result1.out", std::ofstream::out | std::ofstream::trunc);
        
        std::fstream mancheck2("..\\..\\tests\\validation\\manual_check2.txt");
        std::fstream randfis2("..\\..\\tests\\validation\\input_rand2.in");
        std::fstream progfos2("..\\..\\tests\\validation\\program_result2.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream mancheck3("..\\..\\tests\\validation\\manual_check3.txt");
        std::fstream randfis3("..\\..\\tests\\validation\\input_rand3.in");
        std::fstream progfos3("..\\..\\tests\\validation\\program_result3.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream mancheck4("..\\..\\tests\\validation\\manual_check4.txt");
        std::fstream randfis4("..\\..\\tests\\validation\\input_rand4.in");
        std::fstream progfos4("..\\..\\tests\\validation\\program_result4.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream mancheck5("..\\..\\tests\\validation\\manual_check5.txt");
        std::fstream randfis5("..\\..\\tests\\validation\\input_rand5.in");
        std::fstream progfos5("..\\..\\tests\\validation\\program_result5.out", std::ofstream::out | std::ofstream::trunc);
       
        std::fstream mancheck6("..\\..\\tests\\validation\\manual_check6.txt");
        std::fstream randfis6("..\\..\\tests\\validation\\input_rand6.in");
        std::fstream progfos6("..\\..\\tests\\validation\\program_result6.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream mancheck7("..\\..\\tests\\validation\\manual_check7.txt");
        std::fstream randfis7("..\\..\\tests\\validation\\input_rand7.in");
        std::fstream progfos7("..\\..\\tests\\validation\\program_result7.out", std::ofstream::out | std::ofstream::trunc);
        
        std::fstream mancheck8("..\\..\\tests\\validation\\manual_check8.txt");
        std::fstream randfis8("..\\..\\tests\\validation\\input_rand8.in");
        std::fstream progfos8("..\\..\\tests\\validation\\program_result8.out", std::ofstream::out | std::ofstream::trunc);

        std::fstream mancheck9("..\\..\\tests\\validation\\manual_check9.txt");
        std::fstream randfis9("..\\..\\tests\\validation\\input_rand9.in");
        std::fstream progfos9("..\\..\\tests\\validation\\program_result9.out", std::ofstream::out | std::ofstream::trunc);


        test_file_e2e(randfis1, progfos1);
        test_file_e2e(randfis2, progfos2);
        test_file_e2e(randfis3, progfos3);
        test_file_e2e(randfis4, progfos4);
        test_file_e2e(randfis5, progfos5);
        test_file_e2e(randfis6, progfos6);
        test_file_e2e(randfis7, progfos7);
        test_file_e2e(randfis8, progfos8);
        test_file_e2e(randfis9, progfos9);

        progfos1.close();
        progfos2.close();
        progfos3.close();
        progfos4.close();
        progfos5.close();
        progfos6.close();
        progfos7.close();
        progfos8.close();
        progfos9.close();

        std::fstream progf1("..\\..\\tests\\validation\\program_result1.out");
        std::fstream progf2("..\\..\\tests\\validation\\program_result2.out");
        std::fstream progf3("..\\..\\tests\\validation\\program_result3.out");
        std::fstream progf4("..\\..\\tests\\validation\\program_result4.out");
        std::fstream progf5("..\\..\\tests\\validation\\program_result5.out");
        std::fstream progf6("..\\..\\tests\\validation\\program_result6.out");
        std::fstream progf7("..\\..\\tests\\validation\\program_result7.out");
        std::fstream progf8("..\\..\\tests\\validation\\program_result8.out");
        std::fstream progf9("..\\..\\tests\\validation\\program_result9.out");

        assert(compare_files(mancheck1, progf1));
        std::cout << "E2E_1 -  done\n";
        assert(compare_files(mancheck2, progf2));  
        std::cout << "E2E_2 -  done\n";
        assert(compare_files(mancheck3, progf3)); 
        std::cout << "E2E_3 -  done\n";
        assert(compare_files(mancheck4, progf4));
        std::cout << "E2E_4 -  done\n";         
        assert(compare_files(mancheck5, progf5)); 
        std::cout << "E2E_5 -  done\n";
        assert(compare_files(mancheck6, progf6));
        std::cout << "E2E_6 -  done\n";
        assert(compare_files(mancheck7, progf7));
        std::cout << "E2E_7 -  done\n";
        assert(compare_files(mancheck8, progf8));
        std::cout << "E2E_8 -  done\n";
        assert(compare_files(mancheck9, progf9)); 

    }

}

#endif
