cmake_minimum_required(VERSION 3.5)
project(Implementacje_sortowan)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic -std=c99 -lm")

set(SOURCE_FILES main.c main.h bubbleSort.h insertionSort.h heapSort.h quickSort.h mergeSort.h countingSort.h bucketSort.h radixSort.h)
add_executable(Implementacje_sortowan ${SOURCE_FILES})