cmake_minimum_required(VERSION 3.16)

project(InterviewSolution VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PDAL REQUIRED IMPORTED_TARGET pdal)

add_subdirectory(pointcloud_lib)
add_subdirectory(main_app)
