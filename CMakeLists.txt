cmake_minimum_required(VERSION 3.28)
project(dfsPentamino)

set(CMAKE_CXX_STANDARD 17)

add_executable(main_exec main.cpp
        Graph.cpp
        Graph.h
        Utility.cpp
        Utility.h
        PentominoGraph.cpp
        PentominoGraph.h)

add_executable(utility_exec Utility.cpp
                Graph.h
                Graph.cpp)
target_compile_definitions(utility_exec PRIVATE RUN_UTILITY_MAIN)
