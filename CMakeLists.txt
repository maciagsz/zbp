cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_COMPILER                  "/usr/bin/clang" CACHE STRING "C compiler" FORCE) # or "/usr/bin/gcc"
SET(CMAKE_C_FLAGS_INIT                "-Wall -Werror -pedantic")
SET(CMAKE_C_FLAGS_DEBUG_INIT          "-g")
SET(CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET(CMAKE_C_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_COMPILER                  "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE) # or "/usr/bin/g++"
SET(CMAKE_CXX_FLAGS_INIT                "-Wall -Werror -pedantic")
SET(CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET(CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

project(ZBP)

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

set(EXEC_NAME ${PROJECT_NAME}_${CMAKE_BUILD_TYPE})

add_executable(${EXEC_NAME}
  runner/src/TestsRunner.cpp
  main.cpp
)

add_subdirectory(poli_dynamic)
add_subdirectory(poli_static)

target_include_directories(${EXEC_NAME}
  PRIVATE
    runner/include
    poli_static/include
    poli_dynamic/include
)

target_link_libraries(${EXEC_NAME}
  PRIVATE
    PoliDynamicLib
    PoliStaticLib
)
