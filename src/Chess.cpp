#include "Chess.h"

Chess::Chess(const std::string &FENstring) {}

Chess::Chess() {
    setStartingBoard();
}

void Chess::setStartingBoard() {
    //kings
    BitboardHandler::add(bitboards[white][king],7,4,true);
    BitboardHandler::add(bitboards[black][king],0,4,true);

    //queens
    BitboardHandler::add(bitboards[white][queen],7,3,true);
    BitboardHandler::add(bitboards[black][queen],0,3,true);

    //rooks
    BitboardHandler::add(bitboards[white][rook],7,0,true);
    BitboardHandler::add(bitboards[white][rook],7,7,true);
    BitboardHandler::add(bitboards[black][rook],0,0,true);
    BitboardHandler::add(bitboards[black][rook],0,7,true);

    //bishops
    BitboardHandler::add(bitboards[white][bishop],7,2,true);
    BitboardHandler::add(bitboards[white][bishop],7,5,true);
    BitboardHandler::add(bitboards[black][bishop],0,2,true);
    BitboardHandler::add(bitboards[black][bishop],0,5,true);

    //knight
    BitboardHandler::add(bitboards[white][knight],7,1,true);
    BitboardHandler::add(bitboards[white][knight],7,6,true);
    BitboardHandler::add(bitboards[black][knight],0,1,true);
    BitboardHandler::add(bitboards[black][knight],0,6,true);

    //pawns
    for (int i = 0; i < 8; i++) {
        BitboardHandler::add(bitboards[white][pawn],6,i,true);
        BitboardHandler::add(bitboards[black][pawn],1,i,true);
    }
}

bitboard Chess::getCombinedBoards() const {
    bitboard result;
    for (int color = 0; color < 2; color++) {
        for (int pieceName = 0; pieceName < 6; pieceName++) {
            result |= bitboards[color][pieceName];
        }
    }
    return result;
}

bool Chess::move(const pos &from, const pos &to) {
    bitboard *fromBoard = getBitboardAtPos(from);
    bitboard *killBoard = getBitboardAtPos(to);
    if (fromBoard == nullptr) {
        Logger::writeError(errorStream, "No piece at startLocation");
        return false;
    }
    BitboardHandler::del(*fromBoard, from.first, from.second, true);
    BitboardHandler::add(*fromBoard, to.first, to.second, true);

    if (killBoard != nullptr) BitboardHandler::del(*fromBoard, to.first, to.second, true);
}

bitboard *Chess::getBitboardAtPos(const pos &p) {
    for (int color = 0; color < 2; color++) {
        for (int pieceName = 0; pieceName < 6; pieceName++) {
            if (BitboardHandler::isOne(bitboards[color][pieceName], p.first, p.second, true)) {
                return &bitboards[color][pieceName];
            }
        }
    }
    return nullptr;
}

ChessPiece *Chess::getPiece(const pos &p) const {
    for (int color = 0; color < 2; color++) {
        for (int pieceName = 0; pieceName < 6; pieceName++) {
            if (BitboardHandler::isOne(bitboards[color][pieceName], p.first, p.second, true)) {
                return piecePointers[color][pieceName];
            }
        }
    }
    return nullptr;
}

void Chess::print(std::ostream &os) const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(pos(row, col));
            if (piece==nullptr) {
                os << " ";
            } else {
                os << piece->getCharacter();
            }
        }
        os << std::endl;
    }
}

void Chess::setAllMoves(const Color &color) {
    for (int pieceName = 0; pieceName < 6; pieceName++) {
        moves[color][pieceName] = piecePointers[color][pieceName].getMoves(bitboards[color][pieceName]);
    }
}

