cmake_minimum_required(VERSION 3.21)
project(E03 C)

set(CMAKE_C_STANDARD 99)

add_executable(E03 main.c pg.c pg.h inv.c inv.h pgList.c pgList.h invArray.c invArray.h equipArray.c equipArray.h)
