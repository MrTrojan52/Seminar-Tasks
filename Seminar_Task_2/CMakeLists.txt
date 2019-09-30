cmake_minimum_required(VERSION 3.15)
project(Seminar_Task_2)

set(CMAKE_CXX_STANDARD 17)

set(
        SOURCES
        main.cpp
        DeliveryTask.cpp
)

set(
        HEADERS
        DeliveryTask.h
        Definitions.h
        VertexInfo.h
)

add_executable(Seminar_Task_2 ${HEADERS} ${SOURCES})
target_link_libraries(Seminar_Task_2 stdc++fs)