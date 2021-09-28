cmake_minimum_required(VERSION 3.0.0)
project(RayTraycing VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(figures)
include_directories(scene)

file(GLOB FIGURES_SOURCES "figures/*.cpp")
file(GLOB SCENE_SOURCES "scene/*.cpp")

add_executable(RayTraycing main.cpp ${FIGURES_SOURCES} ${SCENE_SOURCES} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
