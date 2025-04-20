cmake_minimum_required(VERSION 3.10.0)
project(Phy_visualizer VERSION 0.0.1 LANGUAGES C CXX)

add_executable(Phy_visualizer 
    dependencies/src/gl.c 
    dependencies/include/glad/gl.h

    include/logs.hpp
    src/logs.cpp
    src/main.cpp
)

target_link_libraries(Phy_visualizer glfw)
