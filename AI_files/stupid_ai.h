#ifndef STUPID_AI_H
#define STUPID_AI_H

#include "possible_boxnpiece.h"
#include "gameitems/gameboard.h"
#include "moves.h"
#include "findallmovess.h"
#include "positioncalcuation.h"
#include <vector>
#include <memory>

typedef std::vector<std::vector<int>> BOARD;

struct MovePacket
{
    MovePacket(BOARD movemap, std::shared_ptr<moves> move, int S) {MoveMap = movemap; Move = move;side =S; value =0;}
    MovePacket(BOARD movemap, std::shared_ptr<moves> move, int S, int V) {MoveMap = movemap; Move = move;side =S; value =V;}
    BOARD MoveMap;   // this map means the map after this move. So if this is your turn now, and this board is the board you are thinkg about, this packet's side should be your opponent's
    std::shared_ptr<moves> Move;
    int side;
    int value;
};

class stupid_AI
{
public:
    PositionCalcuation POS;
    int result = 0;  //check how many Situation this AI is thinking about
    stupid_AI(int side);
    int AIsSide;
    QList <possible_boxNpiece *> *AIsList;
    int maxvalue;
    possible_boxNpiece *current_box_piece;
    void setList(QList <possible_boxNpiece *> *itslist);
    possible_boxNpiece* getMove(QList <possible_boxNpiece *> *itslist);
    std::shared_ptr<MovePacket> getMove(BOARD currentMap, int AISIDE);
    std::shared_ptr<MovePacket> MiniMaxRoot(int depth, BOARD currentMap, int whosTurn);
    double MiniMax(int restDepth, BOARD map,  double alpha, double beta, bool isMaximisingPlayer, int side);
    possible_boxNpiece* chooseAIRandomly();
    std::shared_ptr<MovePacket> findThebestMoveFromOneBoard(std::shared_ptr<findallmovess> HEY);
    std::shared_ptr<moves> findThebestMoveWithoutSearch(findallmovess* AllMoves);
    int evaluateBoard(std::shared_ptr<findallmovess> ListOfMoves, int side);
    int evaluateBoard(BOARD maps,int side);

};

#endif // STUPID_AI_H
