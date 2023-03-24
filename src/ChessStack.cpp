#include "ChessStack.h"
#include "Chess.h"

ChessStack::ChessStack(Chess *c) : c(c) {}

void ChessStack::push() {
    castleRightsStack.push(c->getCastleRights());
    enPassantsStack.push(c->getEnPassant());
    movesStack.push(c->getMoves());
    bitboardsStack.push(c->getBitboards());
    AnDStack.push(c->getAnD());
}

void ChessStack::pop() {
    c->setCastleRights(castleRightsStack.top());
    c->setEnPassant(enPassantsStack.top());
    c->setMoves(movesStack.top());
    c->setBitboards(bitboardsStack.top());
    c->setAnD(AnDStack.top());
    castleRightsStack.pop();
    enPassantsStack.pop();
    movesStack.pop();
    bitboardsStack.pop();
    AnDStack.pop();
}
