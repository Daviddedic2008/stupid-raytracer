cmake_minimum_required(VERSION 3.28)
project(raypathing1)

set(CMAKE_CXX_STANDARD 17)

add_executable(raypathing1 main.cpp
        scene.c
        list.c
        ray.c
        writefile.c
        scenemake.c)
