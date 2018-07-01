#include "stupid_ai.h"


//This has a bug if the AI only has 2 steps to move;

typedef std::vector<std::vector<int>> BOARD;

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

std::shared_ptr<MovePacket> stupid_AI::getMove(BOARD currentMap, int AISIDE)
{
    //std::shared_ptr<findallmovess> currentMoves (new findallmovess(AISIDE, currentMap));
    std::shared_ptr<MovePacket> retPacket;
    //retPacket = findThebestMoveFromOneBoard(currentMoves);// these code are for AI without minimax tree.
    retPacket = MiniMaxRoot (3,currentMap,AISIDE);
    return retPacket;
}

std::shared_ptr<MovePacket> stupid_AI::MiniMaxRoot(int depth, BOARD currentMap, int whosTurn)
{
    result = 0;
    double bestValue = -9999;
    BOARD bestmap = {{}};
    int index =0;
    int moveID = -1;
    std::shared_ptr<findallmovess> AllWeCanDo (new findallmovess(whosTurn,currentMap));
    if (AllWeCanDo->allmaps.length() == 0)
        return NULL;
    for (BOARD maps : AllWeCanDo->allmaps)
    {
        double currentValue = MiniMax(depth -1, maps, -10000, 10000, false, !whosTurn);
        if(currentValue > bestValue)
        {
            bestValue= currentValue;
            bestmap = maps;
            moveID = index;
        }
        else if(currentValue == bestValue)
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            int random =qrand()%3;
            if (random == 2)
            {
                bestValue= currentValue;
                bestmap = maps;
                moveID = index;
            }
        }
        index++;
    }
    std::shared_ptr<moves> bestMove = NULL;
    if (moveID != -1)
        bestMove = AllWeCanDo->allmoves[moveID];
    std::shared_ptr<MovePacket> retPacket (new MovePacket(bestmap,bestMove,whosTurn));
    qDebug()<< "result is "<<result;
    return retPacket;
}

double stupid_AI::MiniMax(int restDepth, BOARD map, double alpha, double beta, bool isMaximisingPlayer, int side)
{
    result ++;
    if(restDepth ==0)
        return evaluateBoard(map, AIsSide); //we need to calcuate AI's side.
    std::shared_ptr<findallmovess> AllNewMoves (new findallmovess(side,map));
    if (isMaximisingPlayer)
    {
        double bestmove = -9999;
        for (BOARD maps : AllNewMoves->allmaps)
        {
            bestmove = std::max(bestmove, MiniMax(restDepth -1, maps, alpha, beta, !isMaximisingPlayer, !side));
            alpha = std::max(alpha, bestmove);
            if (beta <= alpha)
                return bestmove;
        }
        return bestmove;
    }
    else
    {
        double bestmove = 9999;
        for (BOARD maps : AllNewMoves->allmaps)
        {
            bestmove = std::min(bestmove, MiniMax(restDepth -1, maps, alpha, beta, !isMaximisingPlayer, !side));
            beta = std::min(beta, bestmove);
            if (beta <= alpha)
                return bestmove;
        }
        return bestmove;
    }
}

/*
std::shared_ptr<MovePacket> stupid_AI::getTheSmartMove(BOARD currentMap, int AISIDE)
{
    std::shared_ptr<findallmovess> currentMoves (new findallmovess(AISIDE, currentMap));
    std::shared_ptr<MovePacket> retPacket;
    retPacket = findThebestMoveFromOneBoard(currentMoves);;
    return retPacket;
} */


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


std::shared_ptr<MovePacket> stupid_AI::findThebestMoveFromOneBoard(std::shared_ptr<findallmovess> ListOfMoves)
{
    std::shared_ptr<moves> bestMove = NULL;
    int bestValue = -9999;
    int moveID;
    int indexOfMaps = 0;
    BOARD bestmap;
    if (ListOfMoves->allmaps.length() == 0)
        return NULL;
    for (BOARD maps : ListOfMoves->allmaps) {

        //take the negative as AI plays as black
        int boardValue = evaluateBoard(maps,AIsSide);
        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestmap = maps;
            moveID = indexOfMaps;
        }
        indexOfMaps++;
    }
    bestMove = ListOfMoves->allmoves[moveID];
    std::shared_ptr<MovePacket> retPacket (new MovePacket(bestmap,bestMove,ListOfMoves->side));
    return retPacket;
}



std::shared_ptr<moves> stupid_AI::findThebestMoveWithoutSearch(findallmovess* AllMoves)
{
    std::shared_ptr<moves> bestMove = NULL;
    int bestValue = -9999;
    int moveID;
    int indexOfMaps = 0;
    BOARD bestmap;
    for (BOARD maps : AllMoves->allmaps) {

        //take the negative as AI plays as black
        int boardValue = evaluateBoard(maps,AIsSide);
        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestmap = maps;
            moveID = indexOfMaps;
        }
        indexOfMaps++;
    }
    bestMove = AllMoves->allmoves[moveID];
    return bestMove;
}

int stupid_AI::evaluateBoard(std::shared_ptr<findallmovess> ListOfMoves, int side)
{
    int sidecheck;
    if (side)
        sidecheck = -1;
    else
        sidecheck =1;
    int value =0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if (ListOfMoves->map[i][j] == 9 || ListOfMoves->map[i][j] == -9)
                    value += ListOfMoves->map[i][j]*100;
            else if (ListOfMoves->map[i][j] == 8 || ListOfMoves->map[i][j] == -8)
                value += ListOfMoves->map[i][j]*90/8;
            else if (ListOfMoves->map[i][j] == 7 || ListOfMoves->map[i][j] == -7)
                value += ListOfMoves->map[i][j]*50/7;
            else if (ListOfMoves->map[i][j] == 6 || ListOfMoves->map[i][j] == -6)
                value += ListOfMoves->map[i][j]*5;
            else if (ListOfMoves->map[i][j] == 5 || ListOfMoves->map[i][j] == -5)
                value += ListOfMoves->map[i][j]*6;
            else if (ListOfMoves->map[i][j] == 4 || ListOfMoves->map[i][j] == -4)
                value += ListOfMoves->map[i][j]*10/4;
        }
    return value * sidecheck;
}


int stupid_AI::evaluateBoard(BOARD maps, int side)
{
    int sidecheck;
    if (side)
        sidecheck = -1;
    else
        sidecheck =1;
    int value =0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if (maps[i][j] == 9 || maps[i][j] == -9)
                    value += maps[i][j]*100 + ((maps[i][j] <0) ? POS.KingEvalBlack[i][j] : POS.KingEvalWhite[i][j])*maps[i][j]/9;
            else if (maps[i][j] == 8 || maps[i][j] == -8)
                value += maps[i][j]*90/8 + POS.QueenEval[i][j]*maps[i][j]/8;
            else if (maps[i][j] == 7 || maps[i][j] == -7)
                value += maps[i][j]*50/7 + ((maps[i][j] <0) ? POS.RookEvalBlack[i][j] : POS.RookEvalWhite[i][j])*maps[i][j]/7;
            else if (maps[i][j] == 6 || maps[i][j] == -6)
                value += maps[i][j]*5 + POS.KnightEval[i][j]*maps[i][j]/6;
            else if (maps[i][j] == 5 || maps[i][j] == -5)
                value += maps[i][j]*6 + ((maps[i][j] <0) ? POS.BishopEvalBlack[i][j] : POS.BishopEvalWhite[i][j])*maps[i][j]/5;
            else if (maps[i][j] == 4 || maps[i][j] == -4)
                value += maps[i][j]*5/2 + ((maps[i][j] <0) ? POS.PawnEvalBlack[i][j] : POS.PawnEvalWhite[i][j])*maps[i][j]/4;
        }
    return value*sidecheck ;
}


