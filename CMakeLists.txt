cmake_minimum_required(VERSION 3.10)

project(codegenerator)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

find_package(Boost)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

set(SOURCE_FILES main.cpp database.cpp custom_mutex.cpp)
set(HEADER_FILES database.hpp custom_mutex.hpp)

add_custom_target(headers SOURCES ${HEADER_FILES})

add_executable(codegenerator ${SOURCE_FILES})
target_link_libraries(codegenerator ${Boost_LIB} ${PQXX_LIB} ${PQ_LIB})

target_include_directories(codegenerator PRIVATE ${Boost_INCLUDE_DIRS} ${PQXX_INCLUDE_DIRS})
