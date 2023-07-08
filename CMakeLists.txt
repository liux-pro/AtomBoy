cmake_minimum_required(VERSION 3.16.4)

set(CMAKE_TOOLCHAIN_FILE cmake/gcc.cmake)
# Project configuration
project(AtomBoy
        VERSION 1.0.0
        LANGUAGES C CXX ASM)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/GeneratedSrc.cmake)


add_custom_command(TARGET ${RASC_PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${CMAKE_CURRENT_SOURCE_DIR}/build/CMakeFiles/${RASC_PROJECT_NAME}.elf.dir/${RASC_PROJECT_NAME}.elf ${RASC_PROJECT_NAME}.hex
        COMMENT "Building ${HEX_FILE}")