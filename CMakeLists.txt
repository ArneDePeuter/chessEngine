cmake_minimum_required(VERSION 3.24)
project(chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

include_directories(include/boost_1_81_0/)

link_directories(include/boost_1_81_0/)

add_executable(chess
        src/Pieces/Bishop.cpp
        src/Pieces/Bishop.h
        src/defs.h
        src/Chess.cpp
        src/Chess.h
        src/Pieces/Knight.cpp
        src/Pieces/Knight.h
        src/Pieces/Pawn.cpp
        src/Pieces/Pawn.h
        src/Pieces/ChessPiece.cpp
        src/Pieces/ChessPiece.h
        src/Pieces/Queen.cpp
        src/Pieces/Queen.h
        src/Pieces/Rook.cpp
        src/Pieces/Rook.h src/main.cpp src/Pieces/King.h src/Pieces/King.cpp src/BitboardHandler.h src/BitboardHandler.cpp)