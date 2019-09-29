cmake_minimum_required(VERSION 3.14)
project(SpecSem_Lab1)

set(CMAKE_CXX_STANDARD 17)


set(
        SOURCES main.cpp
        BaseLogger.cpp
        HTMLLogger.cpp
        Definitions.cpp
)

set(
        HEADERS IAlgorithm.h
        GreedyAlgorithm.h
        CuttingTask.h
        Definitions.h
        DefaultFactory.h
        IAlgorithmData.h
        BaseAlgorithmData.h
        IStrategy.h
        AStrategy.h
        BasicStrategy.h
        CustomSortingStrategy.h
        CustomBruteforceStrategy.h
        ILogger.h
        BaseLogger.h
        HTMLLogger.h
)


add_executable(SpecSem_Lab1 ${HEADERS} ${SOURCES})
target_link_libraries(SpecSem_Lab1 stdc++fs)