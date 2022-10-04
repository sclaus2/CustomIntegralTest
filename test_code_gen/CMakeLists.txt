cmake_minimum_required(VERSION 3.16)
project(demo_create_and_tabulate LANGUAGES CXX C)

# ------------------------------------------------------------------------------
# Set project name and version number
#project(DOLFINX VERSION "0.5.2.0")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Basix REQUIRED)
find_package(UFCx 0.5 REQUIRED)

message(STATUS "UFCx include dir: ${UFCX_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} main.cpp basix_cwrapper.cpp)
target_link_libraries(${PROJECT_NAME} Basix::basix)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${UFCX_INCLUDE_DIRS})
