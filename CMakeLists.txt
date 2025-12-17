cmake_minimum_required(VERSION 3.10)
project(ProcessListLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(process_list
    main.cpp
    process-list.cpp
    process-list.h
)

target_include_directories(process_list PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
