cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT "C:/Users/rtyse/Downloads/boost_1_89_0-bin-msvc-all-32-64/boost_1_89_0")

# Поиск Boost компонентов
find_package(Boost REQUIRED)

# Включение директорий
include_directories(../include ${Boost_INCLUDE_DIRS})

# Добавление исполняемого файла
add_executable(${PROJECT_NAME}
        graph.hpp
        main.cpp
)

# Связывание с Boost библиотеками
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})