cmake_minimum_required(VERSION 3.5)
project(GoStatistics CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
    Board.cpp
    Group.cpp
    main.cpp
    Turn.cpp
)
