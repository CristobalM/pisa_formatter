cmake_minimum_required(VERSION 3.14)
project(pisa_formatter)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(${CMAKE_SOURCE_DIR}/lib)

add_library(docs_parser docs_parser.hpp docs_parser.cpp)
add_library(terms_reader terms_reader.hpp terms_reader.cpp)

add_executable(pisa_formatter pisa_formatter.cpp util.hpp)
add_executable(query_transformer query_transformer.cpp util.hpp)
add_executable(print_terms print_terms.cpp util.hpp)

target_link_libraries(pisa_formatter docs_parser)
target_link_libraries(query_transformer terms_reader)
target_link_libraries(print_terms terms_reader)
