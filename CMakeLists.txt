cmake_minimum_required(VERSION 3.0.0)
project(RayTraycing VERSION 0.1.0)
#set(CMAKE_CXX_COMPILER "C:\\Program Files\\Codeplay\\ComputeCpp\\bin\\compute++.exe")
include(CTest)
enable_testing()

include_directories(geo)
include_directories(scene)
include_directories(polygon)

file(GLOB GEO_SOURCES "geo/*.cpp")
file(GLOB POLY_SOURCES "polygon/*.cpp")
file(GLOB SCENE_SOURCES "scene/*.cpp")

add_executable(RayTraycing main.cpp ${GEO_SOURCES} ${SCENE_SOURCES} ${POLY_SOURCES})
target_compile_options (RayTraycing PRIVATE -Wgnu-array-member-paren-init -D_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
