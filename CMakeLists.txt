cmake_minimum_required(VERSION 3.15)
project(CAL_Proj)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lib)
include_directories(mapas)
link_libraries(ws2_32 wsock32)

add_executable(CAL_Proj
        lib/connection.cpp
        lib/connection.h
        lib/edgetype.h
        lib/graphviewer.cpp
        lib/graphviewer.h
        lib/Graph.h
        lib/MutablePriorityQueue.h
        main.cpp lib/Node.h)
