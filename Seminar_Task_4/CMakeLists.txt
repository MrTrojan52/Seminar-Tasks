cmake_minimum_required(VERSION 3.15)
project(Seminar_Task_4)

set(CMAKE_CXX_STANDARD 17)
set(FORT_LIB_PATH "../Seminar_Task_3/lib")

set(
        SOURCES
        Definitions.cpp
        main.cpp
        FlowNetworkNode.cpp
        FlowNetwork.cpp
        SupplierTask.cpp
        FordFulkersonSolver.cpp
)

set(
        HEADERS
        Definitions.h
        FlowNetworkNode.h
        FlowNetwork.h
        SupplierTask.h
        IFlowTaskSolver.h
        FordFulkersonSolver.h
)

include_directories(${FORT_LIB_PATH})
add_library(fort_lib STATIC ${FORT_LIB_PATH}/fort.c)

add_executable(Seminar_Task_4 ${HEADERS} ${SOURCES})

target_link_libraries(Seminar_Task_4 stdc++fs fort_lib)