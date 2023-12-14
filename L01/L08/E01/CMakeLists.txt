cmake_minimum_required(VERSION 3.21)
project(E01 C)

set(CMAKE_C_STANDARD 99)

add_executable(E01 main.c dati.c dati.h titoli.c titoli.h quotazioni.c quotazioni.h)
