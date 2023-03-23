#include "Chess.h"

Chess::Chess(const std::string &FENstring) {}

Chess::Chess() {
    setStartingBoard();
}

void Chess::setStartingBoard() {
    toMove = white;

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


bool Chess::move(const pos &from, const pos &to) {
    ChessPiece *fromPiece = getPiece(from, toMove);

    if (fromPiece == nullptr) {
        Logger::writeError(errorStream, "No piece from this color at starting location");
        return false;
    }

    bitboard myMoves = moves[fromPiece->getColor()][fromPiece->getIndex()];

    if (!BitboardHandler::isOne(myMoves, to.first, to.second, true)) {
        Logger::writeError(errorStream, "Invalid Move");
        return false;
    }

    //execute move
    bitboard *fromBoard = &bitboards[fromPiece->getColor()][fromPiece->getIndex()];
    BitboardHandler::del(*fromBoard, from.first, from.second, true);
    BitboardHandler::add(*fromBoard, to.first, to.second, true);

    ChessPiece *toPiece = getPiece(to, swapColor(toMove));
    if (toPiece != nullptr) {
        bitboard *killboard = &bitboards[toPiece->getColor()][toPiece->getIndex()];
        BitboardHandler::del(*killboard, to.first, to.second, true);
    }
    return true;
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
        moves[color][pieceName] = piecePointers[color][pieceName]->getMoves(bitboards[color][pieceName]);
    }
}

ChessPiece *Chess::getPiece(const pos &p, const Color &c) const {
    for (int pieceName = 0; pieceName < 6; pieceName++) {
        if (BitboardHandler::isOne(bitboards[c][pieceName], p.first, p.second, true)) {
            return piecePointers[c][pieceName];
        }
    }
    return nullptr;
}

ChessPiece *Chess::getPiece(const pos &p) const {
    for (Color color : {black, white}) {
        ChessPiece *piece = this->getPiece(p, color);
        if (piece!=nullptr) return piece;
    }
    return nullptr;
}

Color Chess::swapColor(const Color &c) {
    Color result = (c==black) ? white : black;
    return result;
}

bitboard Chess::getCombinedBoards(const Color &color) const {
    bitboard result;
    for (int pieceName = 0; pieceName < 6; pieceName++) {
        result |= bitboards[color][pieceName];
    }
    return result;
}

