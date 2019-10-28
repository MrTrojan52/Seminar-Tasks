cmake_minimum_required(VERSION 3.15)
project(Seminar_Task_3)

set(CMAKE_CXX_STANDARD 17)
include_directories(./lib)
add_library(fort_lib STATIC lib/fort.c)
set(
        SOURCES
        main.cpp
        BaseKnapsackTask.cpp
        DefaultFactory.cpp
        GreedyKnapsackTask.cpp
        BasicSortingStrategy.cpp
        TableKnapsackTask.cpp
        RecursiveKnapsackTask.cpp
        CustomSortingStrategy.cpp
)

set(
        HEADERS
        BaseKnapsackTask.h
        OrderInfo.h
        Definitions.h
        DefaultFactory.h
        GreedyKnapsackTask.h
        ISortingStrategy.h
        BasicSortingStrategy.h
        TableKnapsackTask.h
        RecursiveKnapsackTask.h
        CustomSortingStrategy.h
)


add_executable(Seminar_Task_3 ${HEADERS} ${SOURCES})
target_link_libraries(Seminar_Task_3 stdc++fs fort_lib)