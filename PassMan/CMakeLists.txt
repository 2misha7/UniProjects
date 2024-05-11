cmake_minimum_required(VERSION 3.24)
project(PassMan)

set(CMAKE_CXX_STANDARD 20)

add_executable(PassMan main.cpp Password.cpp Password.hpp PasswordManager.cpp PasswordManager.hpp)
