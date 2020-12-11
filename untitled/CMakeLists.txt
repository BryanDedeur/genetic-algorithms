cmake_minimum_required(VERSION 3.17)

project(main)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp
        GA.cpp GA.h
        Population.cpp Population.h
        Individual.cpp Individual.h
        Utils.cpp Utils.h
        Evaluate.cpp Evaluate.h
        Options.h
        Const.h
        Graph.cpp Graph.h)
