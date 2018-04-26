cmake_minimum_required(VERSION 3.9)
project(AntPathPlanning)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/)

add_executable(AntPathPlanning
        src/main.cpp
        src/jsoncpp.cpp
        src/Map.cpp
        src/Point.cpp
        src/Utils.cpp
        src/Ant.cpp
        src/AntAlgorithm.cpp
        include/Map.h
        include/Point.h
        include/Utils.h
        include/AntAlgorithm.h
        include/Ant.h)

add_executable(Test src/test.cpp)