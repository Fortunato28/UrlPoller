cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(UrlPoller)
include_directories(headers)

set(SOURCES
    src/main.cpp
    src/stream.cpp
    src/socket.cpp
    src/task.cpp)
set(HEADERS
    headers/stream.hpp
    headers/socket.hpp
    headers/task.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
