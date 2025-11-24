cmake_minimum_required(VERSION 3.28.3)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление исполняемого файла
add_executable(${PROJECT_NAME}
        graph.hpp
        main.cpp
)