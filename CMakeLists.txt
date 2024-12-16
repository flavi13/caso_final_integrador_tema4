cmake_minimum_required(VERSION 3.10)

project(caso_final_integrador_tema4 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(caso_final_integrador_tema4
        main.cpp
        main.h
        include/variant.h
        include/variant.cpp
)

include(FetchContent) # se incluye la libreria que necesitamos para el proyecto (json11)
FetchContent_Declare(
        json11
        GIT_REPOSITORY https://github.com/dropbox/json11.git
        GIT_TAG master
)
FetchContent_MakeAvailable(json11)
target_link_libraries(caso_final_integrador_tema4 json11)