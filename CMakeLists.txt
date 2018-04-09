cmake_minimum_required(VERSION 3.10)
project(TheWalk)

set(CMAKE_CXX_STANDARD 11)

add_executable(TheWalk main.cpp Harta.h Joc.h Robot.h Harta_Implementare.cpp StructuriHelper.h Robot_Implementare.cpp Joc_Implementare.cpp)