cmake_minimum_required(VERSION 3.17)
project(AI)

set(CMAKE_CXX_STANDARD 17)
add_executable(
    pbrain-gomoku-ai
    src/Board.cpp
    src/Game.cpp
    src/Utils.cpp
    src/GoProgram.cpp
    src/BitBoard.cpp
    src/GoAI.cpp
    src/main.cpp
    src/Utils.cpp
)

target_include_directories(pbrain-gomoku-ai PUBLIC
    include
)