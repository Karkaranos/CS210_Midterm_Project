cmake_minimum_required(VERSION 3.30)
project(CS210_Midterm_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(CS210_Midterm_Project List.cpp
        HashTable.cpp
        BinarySearchTree.cpp
        cmake-build-debug/SchoolTester.cpp
        SchoolTester.cpp
)
