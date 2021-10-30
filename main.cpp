
#include "scene/bsp_tree.hpp"
#include "tests/test_interception.hpp"
#include "tests/test_vector.hpp"
#include "tests/test_bsp.hpp"
#include "tests/test_e2e.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

rytg::BSPtree bsp;

void parseTriangles(std::istream& is){
    size_t N = 0;
    is >> N;
    double x, y, z;
    std::vector<rytg::Triangle*> triangles(N);
    for(size_t i = 0; i < N; ++i){
        rytg::Point p1, p2, p3;
        is >> x >> y >> z;
        p1 = {x, y, z};
        is >> x >> y >> z;
        p2 = {x, y, z};
        is >> x >> y >> z;
        p3 = {x, y, z};
        triangles[i] = new rytg::Triangle(p1, p2, p3);
        //bsp.add(T);
    }
    for(size_t i = 0; i < N; i++)
        bsp.add(triangles[i]);
}

void print_help(){
    std::cout << "############################################\n";
    std::cout << "Help:\n";
    std::cout << "To use std::cin run: program_name cin | program_name\n";
    std::cout << "To use file write absolute filepath run: program_name folder1/folder2/file.in\n";
    std::cout << "To call help write: program_name --help\n";
    std::cout << "############################################\n";
}

std::string make_path(const char* path){
    bool isWin = false;
#ifdef WIN32
    isWin = true;
#endif
    if(!isWin) return std::string(path);

    std::size_t N = std::strlen(path);
    N += std::count(path, path + N, '\\');
    std::string result;
    result.reserve(N);
    for(const char* it = path; *it != '\0'; it++){
        if(*it != '\\') result.push_back(*it);
        else{
            result.push_back('\\');
            result.push_back('\\');
        }
    }
    return result;

}

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


void generate_output_file(std::vector<rytg::Triangle> trigArray){
    size_t N = trigArray.size();
    std::vector<bool> intersectArray(N, false);
    std::ofstream res("result.txt");
    for ( uint32_t i = 0; i < N-1; i++ ){
        for ( uint32_t j = i + 1; j < N; j++ ){
            //std::cout << "Try : " << i << " - " << j << std::endl;
            if ( trigArray[i].isIntersection(&(trigArray[j])) ){
                    intersectArray[i] = true;
                    intersectArray[j] = true;
                     res << i << " - " << j << std::endl;
            }
        }
    }

    for ( uint32_t i = 0; i < N; ++i ){
        if ( intersectArray[i] )
            res << i << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

int main(int argc, char* argv[]){
    //test_rytg::test_bsp();
    //parseTriangles(std::cin);

    if(argc > 2){
        std::cout << "!!!!!!!!!!!!!!!!\n";
        std::cout << "Wrong arguments\n";
        std::cout << "!!!!!!!!!!!!!!!!\n\n";
        print_help();
        return -1;
    }
    if(argc == 1 || std::strcmp("cin", argv[1]) == 0){
        parseTriangles(std::cin);
    }
    else if(argc == 2 && std::strcmp(argv[1], "--help") == 0){
        print_help();
    }
    else if(argc == 2){
        std::ifstream f(make_path(argv[1]));
        if(f.good()){
            //parseTriangles(f);
            //std::ofstream os("result1.out");
            //auto trigArray = parse_input_file(f);
            //std::cout << trigArray.size() << std::endl;
            //generate_output_file(trigArray);
            //generate_input_file(os);
           // f.close();
            std::ifstream ff(make_path(argv[1]));
            parseTriangles(ff);
        }
        else{
            std::cerr << "can't open file\n";
            return -1;
        }
    }
    return 0;
}
