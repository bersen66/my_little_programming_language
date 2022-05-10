cmake_minimum_required(VERSION 3.16)

project(MY_LITTLE_PROGRAMMING_LANGUAGE)

add_subdirectory(compiler build/compiler)

add_subdirectory(interpreter build/interpreter)
