cmake_minimum_required(VERSION 3.10)

project(caso_final_integrador_tema4 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/path/to/json11)

add_executable(caso_final_integrador_tema4
        main.cpp
        main.h
        ejercicio1/ejercicio1.cpp
        ejercicio2/ejercicio2.cpp
        ejercicio3/ejercicio3.cpp
        ejercicio4/ejercicio4.cpp
        ejercicio5/ejercicio5.cpp
        src/variant.cpp
        include/variant.h
)