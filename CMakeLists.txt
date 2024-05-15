cmake_minimum_required(VERSION 3.25)
project(Data_Structure_Course)

set(CMAKE_CXX_STANDARD 17)
link_libraries(libeasyx.a)
add_executable(Data_Structure_Course src/main.cpp
        src/myAlgorithm.h
        src/file.h
        src/solve.h
)
