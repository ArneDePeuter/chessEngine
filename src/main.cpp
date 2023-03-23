#include "Chess.h"
#include "Pieces/ChessPiece.h"

#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"

#include "defs.h"
#include "iostream"
#include "string"
#include "array"

int main() {
    //Pieceorder {king, queen, rook, bishop, knight, pawn}
    pieceArray piecePointers = {
            std::array<ChessPiece*,6> {
                    new King(black),
                    new Queen(black),
                    new Rook(black),
                    new Bishop(black),
                    new Knight(black),
                    new Pawn(black)                
            },
            {
                    new King(white),
                    new Queen(white),
                    new Rook(white),
                    new Bishop(white),
                    new Knight(white),
                    new Pawn(white)
            }
    };

    std::cout << std::string(*piecePointers[black][queen]) << std::endl;
    
    return 0;
}