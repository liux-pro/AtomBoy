# Configuration file for user settings
# This file should include the path for toolchain and other settings that user would like to override.
set(CMAKE_FIND_ROOT_PATH "D:/e2/gcc-arm-none-eabi-10.3-2021.10/bin" CACHE STRING "toolchain path")

set(COMPILER_OPTIMIZATION "-O2")
string(REPLACE "-O0" ${COMPILER_OPTIMIZATION} RASC_CMAKE_CXX_FLAGS "${RASC_CMAKE_CXX_FLAGS}")
string(REPLACE "-O0" ${COMPILER_OPTIMIZATION} RASC_CMAKE_C_FLAGS "${RASC_CMAKE_C_FLAGS}")
string(REPLACE "-O0" ${COMPILER_OPTIMIZATION} RASC_CMAKE_ASM_FLAGS "${RASC_CMAKE_ASM_FLAGS}")


function(add_include_path_to_flags header_path)
    set(RASC_CMAKE_C_FLAGS "-I ${header_path} ${RASC_CMAKE_C_FLAGS}" PARENT_SCOPE)
    set(RASC_CMAKE_CXX_FLAGS "-I ${header_path} ${RASC_CMAKE_CXX_FLAGS}" PARENT_SCOPE)
    set(RASC_CMAKE_ASM_FLAGS "-I ${header_path} ${RASC_CMAKE_ASM_FLAGS}" PARENT_SCOPE)
endfunction()

# 不知道瑞萨在搞什么,target_include_directories不能用
# https://github.com/renesas/fsp/issues/256
add_include_path_to_flags("${CMAKE_CURRENT_SOURCE_DIR}/src/u8g2/csrc")
add_include_path_to_flags("${CMAKE_CURRENT_SOURCE_DIR}/src/u8g2/cppsrc")

