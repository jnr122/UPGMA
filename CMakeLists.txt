cmake_minimum_required(VERSION 3.13)
project(UPGMA)

set(CMAKE_CXX_STANDARD 14)

add_executable(UPGMA main.cpp Tree.cpp Tree.h Cluster.cpp Cluster.h)