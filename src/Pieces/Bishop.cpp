#include "ChessPiece.h"

Bishop::Bishop(Color color) : ChessPiece(color, 'B', "Bishop", 50, bishop) {

}

bitboard Bishop::getMoves(const bitboard &pieces) {
    return 0;
}
