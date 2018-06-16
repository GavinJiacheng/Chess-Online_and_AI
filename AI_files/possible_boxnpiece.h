#ifndef POSSIBLE_BOXNPIECE_H
#define POSSIBLE_BOXNPIECE_H

#include "gameitems/piece.h"
#include "gameitems/boardbox.h"


class possible_boxNpiece
{
public:
    possible_boxNpiece(Piece *P, boardbox *b);
    Piece * targetPiece;
    boardbox * possibleMove;
    int PieceCol;
    int PieceRow;
    int BoxCol;
    int BoxRow;
    Piece * deadPiece;
};

#endif // POSSIBLE_BOXNPIECE_H
