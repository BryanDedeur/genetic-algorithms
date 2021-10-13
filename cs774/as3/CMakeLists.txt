cmake_minimum_required(VERSION 3.13.2)
project(Project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(as3 gacplus.cpp GA.h GA.cpp Const.h Evaluate.h Evaluate.cpp Individual.h Individual.cpp Options.h Population.h Population.cpp Utils.h Utils.cpp)
