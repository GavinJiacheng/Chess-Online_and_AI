#ifndef STUPID_AI_H
#define STUPID_AI_H

#include "possible_boxnpiece.h"
#include "gameitems/gameboard.h"

class stupid_AI
{
public:
    stupid_AI(int side);
    int AIsSide;
    QList <possible_boxNpiece *> *AIsList;
    int maxvalue;
    possible_boxNpiece *current_box_piece;
    void setList(QList <possible_boxNpiece *> *itslist);
    possible_boxNpiece* getMove(QList <possible_boxNpiece *> *itslist);
    possible_boxNpiece* chooseAIRandomly();

};

#endif // STUPID_AI_H
