#ifndef TEST_E2E_HPP
#define TEST_E2E_HPP

#include "scene/bsp_tree.hpp"
#include "geo/point.hpp"
#include "polygon/triangle.hpp"
#include <vector>
#include <ios>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <string>

namespace test_rytg{

std::string make_path(const std::string& path){
    bool isWin = false;
#ifdef WIN32
    isWin = true;
#endif
    if(!isWin) return std::string(path);

    std::size_t N = path.size();
    N += std::count(path.begin(), path.end(), '\\');
    std::string result;
    result.reserve(N);
    for(const auto& it : path){
        if(it != '\\') result.push_back(it);
        else{
            result.push_back('\\');
            result.push_back('\\');
        }
    }
    return result;

}


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

void test_file_e2e(std::ifstream& randfis, std::ofstream& progfos){
    std::vector<rytg::Triangle> trigArray;
    rytg::BSPtree bsp(progfos);

    randfis.seekg(0);
    testParseTriangles(bsp, randfis);
}

bool compare_files(std::ifstream& manualCheck, std::ifstream& progRes){
    uint32_t mcVal = 0,
             prVal = 0;
    bool eof1 = false,
         eof2 = false;

    while(!((eof1 = manualCheck.eof()) || (eof2 =progRes.eof()))){
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

    for(size_t i = 1; i < 10; i++){
        std::ifstream randfis (make_path("../../tests/validation/input_rand" + std::to_string(i) + ".in"));
        std::ofstream progfos (make_path("../../tests/validation/program_result" + std::to_string(i) + ".out"));
        test_file_e2e(randfis, progfos);
    }

    for(size_t i = 1; i < 10; i++){
        std::ifstream mancheck(make_path("../../tests/validation/manual_check" + std::to_string(i) + ".txt"));
        std::ifstream progf   (make_path("../../tests/validation/program_result" + std::to_string(i) + ".out"));
        assert(compare_files(mancheck, progf));
        std::cout << "E2E_" + std::to_string(i) + " -  done\n";
    }
}

}

#endif
