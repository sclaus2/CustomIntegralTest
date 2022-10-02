cmake_minimum_required(VERSION 3.16)
project(demo_create_and_tabulate LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Basix REQUIRED)

add_executable(${PROJECT_NAME} main.c basix_cwrapper.cpp)
target_link_libraries(${PROJECT_NAME} Basix::basix)
