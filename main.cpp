
#include "scene/bsp_tree.hpp"
#include "tests/test_interception.hpp"
#include "tests/test_vector.hpp"
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

int main(int argc, char* argv[]){
    parseTriangles(std::cin);
    /*
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
        if(f.good())
            parseTriangles(f);
        else{
            std::cerr << "can't open file\n";
            return -1;
        }
    }*/
    return 0;
}
