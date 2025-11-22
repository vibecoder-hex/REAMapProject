cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Boost компонентов
find_package(Boost REQUIRED)

# Включение директорий
include_directories(include ${Boost_INCLUDE_DIRS})

# Добавление исполняемого файла
add_executable(${PROJECT_NAME} main.cpp
        graph.h)

# Связывание с Boost библиотеками
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})