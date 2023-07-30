cmake_minimum_required(VERSION 3.25)

project(Aloo)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

# Internal lib
add_library(Curves STATIC src/math_object.cpp)
target_link_libraries(Curves ${Boost_LIBRARIES})

add_executable(Main src/main.cpp)
target_link_libraries(Main Curves)
