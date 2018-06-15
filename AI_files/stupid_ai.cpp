#include "stupid_ai.h"


stupid_AI::stupid_AI(int side, QList<possible_boxNpiece *> itslist)
{
    AIsSide = side;
    AIsList = itslist;
    maxvalue = 0;
    current_box_piece = NULL;
}
