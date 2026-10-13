cmake_minimum_required(VERSION 3.14)
project(ChessGame)

set(CMAKE_CXX_STANDARD 17)

# Automatically download and configure Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Build your game
add_executable(${PROJECT_NAME}
    main.cpp
    Board.cpp
    Pawn.cpp
    Square.cpp
    BoardRenderer.cpp
    Game.cpp
    Bishop.cpp
    Knight.cpp
    Rook.cpp
    Queen.cpp
    King.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)