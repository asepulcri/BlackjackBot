cmake_minimum_required(VERSION 3.24)
project(BlackjackBot)

set(CMAKE_CXX_STANDARD 23)

add_executable(BlackjackBot main.cpp)

target_include_directories(BlackjackBot PUBLIC include)