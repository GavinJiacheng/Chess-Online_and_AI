#include "stupid_ai.h"


stupid_AI::stupid_AI(int side)
{
    AIsSide = side;
    maxvalue = 0;
    current_box_piece = NULL;
}



void stupid_AI::setList(QList<possible_boxNpiece *> *itslist)
{
    AIsList = itslist;
}

possible_boxNpiece *stupid_AI::getMove(QList<possible_boxNpiece *>* itslist)
{
    setList(itslist);
    return chooseAIRandomly();
}

possible_boxNpiece *stupid_AI::chooseAIRandomly()
{
    int len = (*AIsList).length();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if (len == 0)
        return NULL;
    int random =qrand()%len;
    possible_boxNpiece* ret = (*AIsList)[random];
    return ret;
}
