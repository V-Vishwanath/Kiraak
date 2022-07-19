cmake_minimum_required(VERSION 3.22)
project(Kiraak)

set(CMAKE_CXX_STANDARD 17)

file(GLOB language CONFIGURE_DEPENDS "language/*/*.h" "language/*/*.cpp")

add_executable(Kiraak main.cpp ${language} language/datatypes/Boolean.h)
