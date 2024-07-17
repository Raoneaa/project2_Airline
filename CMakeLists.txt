cmake_minimum_required(VERSION 3.28)
project(Project2_Airline C)

set(CMAKE_C_STANDARD 99)

add_executable(testingCode main.c
        route-records.c
        route-records.h)
