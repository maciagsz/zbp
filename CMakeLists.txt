cmake_minimum_required(VERSION 3.10)

project(ZBP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
  main.cpp
)

set(EXEC_NAME ${PROJECT_NAME}_${CMAKE_BUILD_TYPE})

add_executable(${EXEC_NAME} ${SOURCES})

add_subdirectory(poli_dynamic)
add_subdirectory(poli_static)

target_include_directories(${EXEC_NAME}
  PRIVATE
    poli_static/include
    poli_dynamic/include
)

target_link_libraries(${EXEC_NAME}
  PRIVATE
    PoliDynamicLib
    PoliStaticLib
)
