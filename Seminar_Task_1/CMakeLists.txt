cmake_minimum_required(VERSION 3.14)
project(SpecSem_Lab1)

set(CMAKE_CXX_STANDARD 17)


set(SOURCES main.cpp GreedyAlgorithm.cpp CuttingTask.cpp)
set(HEADERS IAlgorithm.h GreedyAlgorithm.h CuttingTask.h)


add_executable(SpecSem_Lab1 ${HEADERS} ${SOURCES})
target_link_libraries(SpecSem_Lab1 stdc++fs)