cmake_minimum_required(VERSION 3.19)
project(smash)

set(CMAKE_CXX_STANDARD 11)

add_executable(smash commands.cpp signals.cpp smash.cpp signals.h commands.h)