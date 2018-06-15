#ifndef STUPID_AI_H
#define STUPID_AI_H

#include "possible_boxnpiece.h"
#include "gameitems/gameboard.h"

class stupid_AI
{
public:
    stupid_AI(int side, QList <possible_boxNpiece *> itslist);
    int AIsSide;
    QList <possible_boxNpiece *> AIsList;
    int maxvalue;
    possible_boxNpiece *current_box_piece;

};

#endif // STUPID_AI_H
