cmake_minimum_required(VERSION 3.16)

project(parsing_stuff)

set(
        SOURCES
        parsing_stuff.cpp
)

set(
        HEADERS
        parsing_stuff.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
