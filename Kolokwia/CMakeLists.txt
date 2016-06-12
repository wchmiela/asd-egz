cmake_minimum_required(VERSION 3.5)
project(Kolokwia)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic -std=c99 -lm")

set(SOURCE_FILES main.c k1-zad3-15-16.h main.h k1-zad1-15-16.h k2-zad1-15-16.h k2-zad3-15-16.h)
add_executable(Kolokwia ${SOURCE_FILES})