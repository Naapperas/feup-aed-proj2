cmake_minimum_required(VERSION 3.21)
project(project2)

set(CMAKE_CXX_STANDARD 23)

add_executable(project2 main.cpp include/busCompany.h src/busCompany.cpp src/busCompany.h)
