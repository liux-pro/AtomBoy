cmake_minimum_required(VERSION 3.24)
project(AtomBoyEmulator)

set(CMAKE_C_COMPILER "cc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_NO_SYSTEM_FROM_IMPORTED YES)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


file(GLOB SRCS_EMULATOR
        ../src/u8g2/csrc/*.c ../src/u8g2/cppsrc/*.cpp
        u8g2_sdl/*.c
        Arduino/*.c Arduino/*.cpp
        ../src/utils.cpp
        ../src/main.cpp
        fps/*.cpp fps/*.c
        *.c *.cpp)

file(GLOB_RECURSE SRCS_APP
        ../src/app/*.c ../src/app/*.cpp
        )


include_directories(fps/)
include_directories(Arduino/)
include_directories(.)

include_directories(../src/u8g2/csrc/)
include_directories(../src/u8g2/cppsrc/)
include_directories(../src/)


add_executable(AtomBoyEmulator ${SRCS_EMULATOR} ${SRCS_APP})


target_link_libraries(AtomBoyEmulator ${SDL2_LIBRARIES})

