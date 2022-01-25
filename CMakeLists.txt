cmake_minimum_required(VERSION 3.21)
project(project2)

set(CMAKE_CXX_STANDARD 23)

add_executable(project2 main.cpp include/busCompany.h src/busCompany.cpp include/stop.h src/stop.cpp include/graph.h src/graph.cpp include/utils.h src/utils.cpp include/busLine.h src/busLine.cpp)
