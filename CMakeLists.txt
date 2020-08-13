cmake_minimum_required(VERSION 3.15)
project(trees)

set(CMAKE_CXX_STANDARD 14)

add_executable(trees main.cpp pch.h Tree.h Tree.cpp TreeNode.cpp TreePrinter.cpp AvlNode.cpp RbNode.cpp)