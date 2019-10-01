cmake_minimum_required(VERSION 3.15)
project(Seminar_Task_2)

set(CMAKE_CXX_STANDARD 17)

set(
        SOURCES
        main.cpp
        DeliveryTask.cpp
        DefaultFactory.cpp
        BaseBranchingStrategy.cpp
        BaseLowerBoundStrategy.cpp
        BaseUpperBoundStrategy.cpp
        ABoundStrategy.cpp
        CustomBranchingStrategy.cpp
        BaseLogger.cpp
        HTMLLogger.cpp
)

set(
        HEADERS
        DeliveryTask.h
        Definitions.h
        VertexInfo.h
        ILowerBoundStrategy.h
        IUpperBoundStrategy.h
        IBranchingStrategy.h
        DefaultFactory.h
        BaseBranchingStrategy.h
        BaseLowerBoundStrategy.h
        BaseUpperBoundStrategy.h
        ABoundStrategy.h
        CustomBranchingStrategy.h
        ILogger.h
        BaseLogger.h
        HTMLLogger.h
)

add_executable(Seminar_Task_2 ${HEADERS} ${SOURCES})
target_link_libraries(Seminar_Task_2 stdc++fs)