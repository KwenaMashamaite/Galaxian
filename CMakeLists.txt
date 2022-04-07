# Set CMake version
cmake_minimum_required(VERSION 3.21)

# Set project details
project(Galaxian LANGUAGES CXX VERSION 0.1.0 DESCRIPTION "1979 Galaxian arcade game clone using C++17 and IME")

# Set CXX version used by the project
set(CMAKE_CXX_STANDARD 17)

#Build game
add_subdirectory(src)