
#include "scene/bsp_tree.hpp"
#include "tests/tests.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>



void parseTriangles(std::istream& is, std::ostream& os){
    test_rytg::tests_unite();
    rytg::BSPtree bsp(os);
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
        bsp.add(new rytg::Triangle(p1, p2, p3));
    }
}

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

void print_help(){
    std::cout << "############################################\n";
    std::cout << "Help:\n";
    std::cout << "To use std::cin run: program_name cin | program_name\n";
    std::cout << "To use file write absolute filepath run: program_name folder1/folder2/file.in\n";
    std::cout << "To call help write: program_name --help\n";
    std::cout << "############################################\n";
}



int main(int argc, char* argv[]){
    if(argc > 3){
        std::cout << "!!!!!!!!!!!!!!!!\n";
        std::cout << "Wrong arguments\n";
        std::cout << "!!!!!!!!!!!!!!!!\n\n";
        print_help();
        return -1;
    }
    if(argc == 1 || std::strcmp("cin", argv[1]) == 0){
        parseTriangles(std::cin, std::cout);
    }
    else if(argc == 2 && std::strcmp(argv[1], "--help") == 0){
        print_help();
    }
    else if(argc == 2 || argc == 3){
        std::string path = argv[1];
        std::ifstream f(make_path(path));
        if(f.good()){
            if(argc == 3){
                std::ofstream os(make_path(argv[2]));
                parseTriangles(f, os);
            }
            else
                parseTriangles(f, std::cout);
        }
        else{
            std::cerr << "can't open file\n";
            return -1;
        }
    }
    return 0;
}
