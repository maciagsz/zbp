set(NAME PoliStaticLib)

add_library(${NAME} STATIC
    src/Addition.cpp
    src/Hashing.cpp
)

target_include_directories(${NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
