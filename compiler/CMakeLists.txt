cmake_minimum_required(VERSION 3.16)
project(COMPILER)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -Ofast)

find_package(Boost COMPONENTS regex REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(
        SOURCES
        main.cpp
        token.cpp
)

set(
        HEADERS
        grammar.h
        token.h
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})

