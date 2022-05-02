cmake_minimum_required(VERSION 3.21)

project(INTERPRETER)
set(CMAKE_CXX_STANDARD 20)


add_subdirectory(parsers)
include_directories(parsers)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


set(
        SOURCES
        main.cpp
        virtual_machine.cpp
        objects/object.cpp
)

set(
        HEADERS
        virtual_machine.h
        objects/object.h
        instructions.h
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} parsing_stuff)
target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})
