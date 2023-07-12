cmake_minimum_required(VERSION 3.24.0)


set(CMAKE_TOOLCHAIN_FILE cmake/gcc.cmake)
# Project configuration
project(AtomBoy
        VERSION 1.0.0
        LANGUAGES C CXX ASM)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/GeneratedSrc.cmake)

set(ELF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/CMakeFiles/${RASC_PROJECT_NAME}.elf.dir/${RASC_PROJECT_NAME}.elf)

add_custom_command(TARGET ${RASC_PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${ELF_PATH} ${RASC_PROJECT_NAME}.hex
        COMMENT "Building ${RASC_PROJECT_NAME}.hex")


add_custom_target(flash
        COMMAND python -m pyocd flash ${ELF_PATH} --target R7FA2E1A7 --pack "${CMAKE_CURRENT_SOURCE_DIR}/R7FA2E1A7.pack"
        COMMENT "Flash ${RASC_PROJECT_NAME}.hex"
        DEPENDS ${RASC_PROJECT_NAME}.elf
        )


SET(SIZE ${CMAKE_FIND_ROOT_PATH}/arm-none-eabi-size${BINARY_FILE_EXT})
add_custom_command(TARGET ${RASC_PROJECT_NAME}.elf POST_BUILD
        COMMAND ${SIZE} ${ELF_PATH}
        )
