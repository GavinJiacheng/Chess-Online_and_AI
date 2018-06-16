#include "possible_boxnpiece.h"


possible_boxNpiece::possible_boxNpiece(Piece *P, boardbox *b)
{
    targetPiece = P;
    possibleMove = b;
    PieceCol = P->getCol();
    PieceRow = P->getRow();
    BoxCol = b->getCol();
    BoxRow = b->getRow();
    if (b->hasPiece())
        deadPiece = b->getpiece();
    else
        deadPiece = NULL;
}
