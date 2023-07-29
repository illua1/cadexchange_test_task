cmake_minimum_required(VERSION 3.25)

project(Aloo)

# Boosl include
set(BOOST_ROOT "C:/Boost")
set(BOOST_INCLUDEDIR "C:/Boost/include/boost-1_82")

find_package(Boost)

include_directories(${Boost_INCLUDE_DIRS})

# Internal libs
add_library(Math STATIC src/math_object.cpp)
target_link_libraries(Math ${Boost_LIBRARIES})

add_executable(Main src/main.cpp)
target_link_libraries(Main Math)
