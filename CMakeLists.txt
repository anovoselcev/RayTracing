cmake_minimum_required(VERSION 3.0.0)
project(RayTracing VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILER "C:\\Program Files\\Codeplay\\ComputeCpp\\bin\\compute++.exe")

#set(CMAKE_MODULE_PATH /path/to/computecpp-sdk/cmake/Modules/)

#include_directories(${COMPUTECPP_INCLUDE_DIRECTORY})

include_directories(geo)
include_directories(scene)
include_directories(polygon)

file(GLOB GEO_SOURCES "geo/*.cpp")
file(GLOB POLY_SOURCES "polygon/*.cpp")
file(GLOB SCENE_SOURCES "scene/*.cpp")

add_executable(RayTracing main.cpp ${GEO_SOURCES} ${SCENE_SOURCES} ${POLY_SOURCES})
target_compile_options (RayTracing PRIVATE -Wgnu-array-member-paren-init)
