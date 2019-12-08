cmake_minimum_required(VERSION 3.15)
project(Seminar_Task_5)

set(CMAKE_CXX_STANDARD 17)
set(FORT_LIB_PATH "../Seminar_Task_3/lib")

set(
        SOURCES
        main.cpp
        SalesmanTask.cpp
        BaseReductionStrategy.cpp
        DefaultFactory.cpp
)

set(
        HEADERS
        Definitions.h
        Point.h
        City.h
        SalesmanTask.h
        IReductionStrategy.h
        BaseReductionStrategy.h
        DefaultFactory.h
)


include_directories(${FORT_LIB_PATH})
add_library(fort_lib STATIC ${FORT_LIB_PATH}/fort.c)

add_executable(Seminar_Task_5 ${HEADERS} ${SOURCES})

target_link_libraries(Seminar_Task_5 stdc++fs fort_lib)