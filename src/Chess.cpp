#include "Chess.h"
#include "ChessStack.h"

Chess::Chess(const std::string &FENstring) {}

Chess::Chess() {
    undostack = new ChessStack(this);
    redostack = new ChessStack(this);
    setStartingBoard();
    update();
}

void Chess::setStartingBoard() {
    toMove = white;
    castleRights = {true, true, true, true};

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

    if (!BitboardHandler::isOne(myMoves, to.first, to.second, true) || !validCastle(fromPiece, from, to)) {
        Logger::writeError(errorStream, "Invalid Move");
        return false;
    }
    undostack->push();

    //execute move
    bitboard *fromBoard = &bitboards[fromPiece->getColor()][fromPiece->getIndex()];
    BitboardHandler::del(*fromBoard, from.first, from.second, true);
    BitboardHandler::add(*fromBoard, to.first, to.second, true);

    ChessPiece *toPiece = getPiece(to, swapColor(toMove));
    if (toPiece != nullptr) {
        bitboard *killBoard = &bitboards[toPiece->getColor()][toPiece->getIndex()];
        BitboardHandler::del(*killBoard, to.first, to.second, true);
    }
    handleEnpassant(fromPiece, from, to);

    swap();
    return true;
}

void Chess::print(std::ostream &os) const {
    os << std::endl;
    for (int row = 0; row < 8; row++) {
        os << 8 - row << " |";
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(pos(row, col));
            if (piece==nullptr) {
                os << " ";
            } else {
                os << piece->getCharacter();
            }
            os << " ";
        }
        os << std::endl;
    }
    os << "  |";
    for (int i = 0; i < 8; i++) {
        os << "__";
    }
    os << std::endl << "  |";
    char c = 'a';
    for (int i = 0; i < 8; i++) {
        os << c << " ";
        c++;
    }
    os << std::endl;
    os << std::endl;
    os << "To Move: " << ((toMove==black) ? "Black" : "White") << std::endl;
    os << std::endl;
    os << "Check: " << std::boolalpha << check() << std::endl;
    os << "Checkmate: " << std::boolalpha << checkmate() << std::endl;
    os << "Stalemate: " << std::boolalpha << stalemate() << std::endl;
    os << std::endl;
    os << "Castle King White: " << std::boolalpha << castleRights[wCastleK] << std::endl;
    os << "Castle Queen White: " << std::boolalpha << castleRights[wCastleQ] << std::endl;
    os << "Castle King Black: " << std::boolalpha << castleRights[bCastleK] << std::endl;
    os << "Castle Queen Black: " << std::boolalpha << castleRights[bCastleQ] << std::endl;
    os << std::endl;

}

void Chess::update() {
    setPinLaser();
    setKingAttackers();
    for (int pieceName = 0; pieceName < 6; pieceName++) {
        moves[toMove][pieceName] = piecePointers[toMove][pieceName]->getMoves(bitboards[toMove][pieceName]&~pinLaser,
                                                                            getCombinedBoards(toMove),
                                                                            getCombinedBoards(swapColor(toMove)), false);
        if (kingAttackers>((bitboard)0)) {
            moves[toMove][pieceName] &= kingAttackers;
        }
    }
    setAnD();
    moves[toMove][king] &= ~AnD;
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

void Chess::setPinLaser() {
    pinLaser = ((bitboard) 0);
    bitboard enemySliders = bitboards[swapColor(toMove)][rook] | bitboards[swapColor(toMove)][queen] | bitboards[swapColor(toMove)][bishop];
    Queen kingQueen = Queen(toMove);

    bitboard pinMask = kingQueen.getMoves(bitboards[toMove][king], getCombinedBoards(toMove), getCombinedBoards(swapColor(toMove)),true);


    std::array<int, 8> directions = {
            FORWARD, BACKWARD, LEFT, RIGHT, FORWARD+LEFT, FORWARD+RIGHT, BACKWARD+LEFT, BACKWARD+RIGHT
    };
    bitboard slide;
    for (int direction : directions) {
        slide = kingQueen.slideToDir(bitboards[toMove][king], getCombinedBoards(toMove)&~pinMask, getCombinedBoards(swapColor(toMove)), {direction}, false);
        if (slide&enemySliders) {
            pinLaser |= slide;
        }
    }
}

void Chess::setAnD() {
    for (int pieceName = 0; pieceName < 6; pieceName++) {
        AnD |= piecePointers[swapColor(toMove)][pieceName]->getMoves(bitboards[swapColor(toMove)][pieceName]&pinLaser,
                                                                              getCombinedBoards(swapColor(toMove)),
                                                                              getCombinedBoards(toMove), true);
    }
}

void Chess::swap() {
    toMove = swapColor(toMove);
    update();
}

bool Chess::check() const {
    return static_cast<bool>(bitboards[toMove][king]&AnD);
}

bool Chess::checkmate() const {
    bool hasMoves=false;
    for (int pieceIndex = 0; pieceIndex < 6; ++pieceIndex) {
        hasMoves = hasMoves || moves[toMove][pieceIndex];
    }
    return check() && !hasMoves;
}

bool Chess::stalemate() const {
    bool hasMoves=false;
    for (int pieceIndex = 0; pieceIndex < 6; ++pieceIndex) {
        hasMoves = hasMoves || moves[toMove][pieceIndex];
    }
    return !check() && !hasMoves;
}

void Chess::setKingAttackers() {
    kingAttackers = (bitboard (0));
    for (int pieceIndex = 0; pieceIndex < 6; pieceIndex++) {
        ChessPiece* imitatingKing = piecePointers[toMove][pieceIndex];
        bitboard attacked = imitatingKing->getMoves(bitboards[toMove][king], getCombinedBoards(toMove), getCombinedBoards(swapColor(toMove)), true);
        bitboard attackers = bitboards[swapColor(toMove)][pieceIndex] & attacked;
        if (attackers>((bitboard)0)){
            kingAttackers |= attackers | (attacked & imitatingKing->getMoves(attackers, getCombinedBoards(swapColor(toMove)), getCombinedBoards(toMove), false));
        }
    }
}

bool Chess::gameOver() {
    return stalemate() || checkmate();
}

void Chess::handleEnpassant(ChessPiece *movedPiece, const pos &from, const pos &to) {
    if (!dynamic_cast<Pawn*>(movedPiece)) {
        enPassant = 0;
        return;
    }

    bitboard toBoard;
    BitboardHandler::add(toBoard, to.first, to.second, true);
    if (abs(from.first-to.first)==2) {
        BitboardHandler::add(enPassant, from.first+(to.first-from.first)/2, from.second,true);
        return;
    } else if (toBoard&enPassant) {
        BitboardHandler::del(bitboards[swapColor(toMove)][pawn],from.first,to.second,true);
    }
    enPassant = 0;
}

bool Chess::validCastle(ChessPiece *movedPiece, const pos &from, const pos &to) {
    if (dynamic_cast<Rook*>(movedPiece)) {
        if (from == pos(0,0)) castleRights[bCastleQ] = false;
        if (from == pos(0,7)) castleRights[bCastleK] = false;
        if (from == pos(7,0)) castleRights[wCastleQ] = false;
        if (from == pos(7,7)) castleRights[wCastleK] = false;
        return true; //ignore
    } else if (!dynamic_cast<King*>(movedPiece)) {
        if (to == pos(0,0)) castleRights[bCastleQ] = false;
        if (to == pos(0,7)) castleRights[bCastleK] = false;
        if (to == pos(7,0)) castleRights[wCastleQ] = false;
        if (to == pos(7,7)) castleRights[wCastleK] = false;
        return true; //ignore
    }

    bool *castleK = (movedPiece->getColor()==black) ? &castleRights[bCastleK] : &castleRights[wCastleK];
    bool *castleQ = (movedPiece->getColor()==black) ? &castleRights[bCastleQ] : &castleRights[wCastleQ];

    if (!*castleK && !*castleQ) return true;

    if (from.first!=to.first) {
        *castleK = false;
        *castleQ = false;
        return true;
    } else if (abs(from.second-to.second)!=2) {
        *castleK = false;
        *castleQ = false;
        return true;
    }

    bool *castleRight = (to.second==6) ? castleK : castleQ;
    int sign = (to.second-from.second)/2;


    bitboard combined = getCombinedBoards(toMove)|getCombinedBoards(swapColor(toMove));
    if (*castleRight
        &&!(BitboardHandler::isOne(combined, from.first, to.second, true)
        ||BitboardHandler::isOne(combined, from.first, from.second+sign, true)
        ||check()
        ||BitboardHandler::isOne(AnD, from.first, to.second, true)
        ||BitboardHandler::isOne(AnD, from.first, from.second+sign, true))) {

        BitboardHandler::add(bitboards[toMove][rook], from.first, from.second+sign, true);
        BitboardHandler::del(bitboards[toMove][rook], from.first, (to.second==2) ? 0 : 7 , true);

        *castleK = false;
        *castleQ = false;
        return true;
    } else {
        return false;
    }
}

const bitboard &Chess::getEnPassant() const {
    return enPassant;
}

const castleRightsArray &Chess::getCastleRights() const {
    return castleRights;
}

const bitboardArray &Chess::getBitboards() const {
    return bitboards;
}

const bitboardArray &Chess::getMoves() const {
    return moves;
}

const bitboard &Chess::getAnD() const {
    return AnD;
}

void Chess::setEnPassant(const bitboard &enPassant) {
    Chess::enPassant = enPassant;
}

void Chess::setCastleRights(const castleRightsArray &castleRights) {
    Chess::castleRights = castleRights;
}

void Chess::setBitboards(const bitboardArray &bitboards) {
    Chess::bitboards = bitboards;
}

void Chess::setMoves(const bitboardArray &moves) {
    Chess::moves = moves;
}

void Chess::setAnD(const bitboard &anD) {
    AnD = anD;
}

void Chess::undo() {
    redostack->push();
    undostack->pop();
    toMove = swapColor(toMove);
}

void Chess::redo() {
    undostack->push();
    redostack->pop();
    toMove = swapColor(toMove);
}

