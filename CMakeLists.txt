cmake_minimum_required(VERSION 3.15)

set (CMAKE_CXX_STANDARD 17)

project (cdist)
set (cdist_VERSION_MAJOR 1)
set (cdist_VERSION_MINOR 0)
set (cdist_VERSION "${cdist_VERSION_MAJOR}.${cdist_VERSION_MINOR}")

add_definitions ("-Wall")

file(GLOB CPPS "source/*.cpp")
file(GLOB HS   "source/*.h")

add_executable(main ${CPPS} ${HS})
