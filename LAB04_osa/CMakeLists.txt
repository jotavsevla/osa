cmake_minimum_required(VERSION 3.10)
project(LAB04_osa)

set(CMAKE_CXX_STANDARD 17)

add_executable(LAB04_osa
        main.cpp
        Book.cpp
        FileManager.cpp
)

target_include_directories(LAB04_osa PRIVATE include)