#include "findallmovess.h"


findallmovess::findallmovess(int SIDE, std::vector<std::vector<int>> MAP)
{

    side = SIDE;
    int sidecheck = 1 - SIDE - SIDE;
    for (int i=0; i<8; i++)
    {
        for (int j = 0; j <8;j++)
                 map[i][j]=MAP[i][j];
    }
    //Find "King's Landing"!!!
    for (int i=0; i<8; i++)
    {
        for (int j = 0; j <8;j++)
            {
                 if (map[i][j] == 9 * sidecheck)
                 {
                     kingslanding[0] = i;
                     kingslanding[1] = j;
                     break;
                 }
            }
    }

    for (int i=0; i<8; i++)
    {
        for (int j = 0; j <8;j++)
                 if (sidecheck * map[i][j] > 0)
                     findMovesFor(i,j);
    }
}



void findallmovess::findMovesFor(int x, int y)
{
    int type = map[x][y];
    if (type == 9 || type == -9)
        kingsmove(x,y);
    else if (type == 8 || type == -8)
        queensmove(x,y);
    else if (type == 7 || type == -7)
        rooksmove(x,y);
    else if (type == 6 || type == -6)
        knightsmove(x,y);
    else if (type == 5 || type == -5)
        bishopsmove(x,y);
    else if (type == 4 || type == -4)
        pawnsmove(x,y);
}

void findallmovess::kingsmove(int px, int py)
{
    int sidecheck;
    int P = map[px][py];
    if (P > 0)
        sidecheck = 1;
    else
        sidecheck = -1;
    int Startx =px-1;
    int Starty =py-1;
    if (Startx < 0)
        Startx++;
    if (Starty < 0)
        Starty++;
    int x, y;
    for (x = Startx; x < px+2 && x <8; x++)
    {
        for(y = Starty; y<py+2 && y<8;y++)
        {
                if (map[x][y] == 0)
                {
                    std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));

                    //  old code
                    //int **new_board=new int *[8];
                    //for (int i=0; i<8; i++)
                    //{
                    //    new_board[i] = new int[8];
                    //    for (int j = 0; j <8;j++)
                    //             new_board[i][j] = map[i][j];
                    //}


                    // new code
                    std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                    for (int i=0; i<8; i++)
                    {
                        for (int j = 0; j <8;j++)
                                 new_board[i][j] = map[i][j];
                    }

                    // are they same?


                    new_board[px][py] = 0;
                    new_board[x][y] = P;
                    if (!attacked(x,y,new_board))
                    {
                        allmoves.append(M);
                        allmaps.append(new_board);
                    }
                }
                else if (map[x][y]*sidecheck < 0)
                {
                    if (map[x][y]*sidecheck == -9)
                        checking = true;
                    std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                    std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                    for (int i=0; i<8; i++)
                    {
                        for (int j = 0; j <8;j++)
                                 new_board[i][j] = map[i][j];
                    }
                    new_board[px][py] = 0;
                    new_board[x][y] = P;
                    if (!attacked(x,y,new_board))
                    {
                        allmoves.append(M);
                        allmaps.append(new_board);
                    }
                }
        }
    }
}

void findallmovess::queensmove(int x, int y)
{
    rooksmove(x,y);
    bishopsmove(x,y);
}

void findallmovess::rooksmove(int px, int py)
{
    int sidecheck;
    int P = map[px][py];
    if (P > 0)
        sidecheck = 1;
    else
        sidecheck = -1;
    int x = px +1;
    int y = py;
    for (; x<8;x++)
    {
        if (map[x][y] == 0)
        {
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
        else if (map[x][y]*sidecheck < 0)
        {
            if (map[x][y]*sidecheck == -9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
            break;
        }
        else
            break;
    }
    x = px -1;
    for (; x>=0;x--)
    {
        if (map[x][y] == 0)
        {
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
        else if (map[x][y]*sidecheck < 0)
        {
            if (map[x][y]*sidecheck == -9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
            break;
        }
        else
            break;
    }
    x = px;
    y = py +1;
    for (; y<8;y++)
    {
        if (map[x][y] == 0)
        {
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
        else if (map[x][y]*sidecheck < 0)
        {
            if (map[x][y]*sidecheck == -9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
            break;
        }
        else
            break;
    }
    y = py -1;
    for (; y>=0;y--)
    {
        if (map[x][y] == 0)
        {
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
        else if (map[x][y]*sidecheck < 0)
        {
            if (map[x][y]*sidecheck == -9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
            break;
        }
        else
            break;
    }
}

void findallmovess::knightsmove(int px, int py)
{
    int sidecheck;
    int P = map[px][py];
    if (P > 0)
        sidecheck = 1;
    else
        sidecheck = -1;
    int x, y;
    if (px+1 < 8)
    {
        if (py+2 <8)
        {
            x = px+1;
            y = py+2;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
            else if (map[x][y]*sidecheck < 0)
            {
                if (map[x][y]*sidecheck == -9)
                    checking = true;
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
        }
        else if (py - 2 >=0)
        {
            x = px+1;
            y = py-2;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
            else if (map[x][y]*sidecheck < 0)
            {
                if (map[x][y]*sidecheck == -9)
                    checking = true;
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
        }
    }

    if (px-1 >= 0)
    {
        if (py+2 <8)
        {
            x = px-1;
            y = py+2;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
            else if (map[x][y]*sidecheck < 0)
            {
                if (map[x][y]*sidecheck == -9)
                    checking = true;
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
        }
        else if (py - 2 >=0)
        {
            x = px-1;
            y = py-2;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
            else if (map[x][y]*sidecheck < 0)
            {
                if (map[x][y]*sidecheck == -9)
                    checking = true;
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
        }
    }

    if (px+2 < 8)
    {
        if (py+1 <8)
        {
            x = px+2;
            y = py+1;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
            else if (map[x][y]*sidecheck < 0)
            {
                if (map[x][y]*sidecheck == -9)
                    checking = true;
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
        }
        else if (py - 1 >=0)
        {
            x = px+2;
            y = py-1;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
            else if (map[x][y]*sidecheck < 0)
            {
                if (map[x][y]*sidecheck == -9)
                    checking = true;
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
        }
    }

    if (px-2 >= 0)
    {
        if (py+1 <8)
        {
            x = px-2;
            y = py+1;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
            else if (map[x][y]*sidecheck < 0)
            {
                if (map[x][y]*sidecheck == -9)
                    checking = true;
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
        }
        else if (py - 1 >=0)
        {
            x = px-2;
            y = py-1;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
            else if (map[x][y]*sidecheck < 0)
            {
                if (map[x][y]*sidecheck == -9)
                    checking = true;
                std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board[i][j] = map[i][j];
                }
                new_board[px][py] = 0;
                new_board[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board))
                {
                    allmoves.append(M);
                    allmaps.append(new_board);
                }
            }
        }
    }
}

void findallmovess::bishopsmove(int px, int py)
{
    int sidecheck;
    int P = map[px][py];
    if (P > 0)
        sidecheck = 1;
    else
        sidecheck = -1;
    int x = px +1;
    int y = py +1;
    for (; x<8 && y <8;x++)
    {
        if (map[x][y] == 0)
        {
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
        else if (map[x][y]*sidecheck < 0)
        {
            if (map[x][y]*sidecheck == -9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
            break;
        }
        else
            break;
        y++;
    }
    x = px +1;
    y = py -1;
    for (; x<8 && y >=0;x++)
    {
        if (map[x][y] == 0)
        {
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
        else if (map[x][y]*sidecheck < 0)
        {
            if (map[x][y]*sidecheck == -9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
            break;
        }
        else
            break;
        y--;
    }
    x = px -1;
    y = py +1;
    for (; x>=0 && y <8;x--)
    {
        if (map[x][y] == 0)
        {
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
        else if (map[x][y]*sidecheck < 0)
        {
            if (map[x][y]*sidecheck == -9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
            break;
        }
        else
            break;
        y++;
    }
    x = px -1;
    y = py -1;
    for (; x>=0 && y >=0; x--)
    {
        if (map[x][y] == 0)
        {
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
        else if (map[x][y]*sidecheck < 0)
        {
            if (map[x][y]*sidecheck == -9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
            break;
        }
        else
            break;
        y--;
    }
}

void findallmovess::pawnsmove(int px, int py)
{
    int P = map[px][py];
    int pace;
    if (P < 0)
        pace = 1;
    else
        pace = -1;
    int x = px;
    int y = py+pace;
    if (map[x][y] == 0)
    {
        std::shared_ptr<moves> M (new moves(P, px, py, x, y, 0));
        std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
        for (int i=0; i<8; i++)
        {
            for (int j = 0; j <8;j++)
                     new_board[i][j] = map[i][j];
        }
        new_board[px][py] = 0;
        new_board[x][y] = P;
        if (!attacked(kingslanding[0],kingslanding[1],new_board))
        {
            allmoves.append(M);
            allmaps.append(new_board);
        }
        if (side && py ==1)
        {
            y = py+pace+pace;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M1 (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board1(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board1[i][j] = map[i][j];
                }
                new_board1[px][py] = 0;
                new_board1[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board1))
                {
                    allmoves.append(M1);
                    allmaps.append(new_board1);
                }
            }
        }
        else if (!side && py ==6)
        {
            y = py+pace+pace;
            if (map[x][y] == 0)
            {
                std::shared_ptr<moves> M1 (new moves(P, px, py, x, y, map[x][y]));
                std::vector<std::vector<int>> new_board1(8,std::vector<int>(8));
                for (int i=0; i<8; i++)
                {
                    for (int j = 0; j <8;j++)
                             new_board1[i][j] = map[i][j];
                }
                new_board1[px][py] = 0;
                new_board1[x][y] = P;
                if (!attacked(kingslanding[0],kingslanding[1],new_board1))
                {
                    allmoves.append(M1);
                    allmaps.append(new_board1);
                }
            }
        }
    }
    y = py + pace;
    x = px + 1;
    if (x <8)
    {
        if (map[x][y] *pace > 0)
        {
            if (map[x][y]*pace == 9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
    }
    y = py + pace;
    x = px - 1;
    if (x >=0)
    {
        if (map[x][y] *pace > 0)
        {
            if (map[x][y]*pace == 9)
                checking = true;
            std::shared_ptr<moves> M (new moves(P, px, py, x, y, map[x][y]));
            std::vector<std::vector<int>> new_board(8,std::vector<int>(8));
            for (int i=0; i<8; i++)
            {
                for (int j = 0; j <8;j++)
                         new_board[i][j] = map[i][j];
            }
            new_board[px][py] = 0;
            new_board[x][y] = P;
            if (!attacked(kingslanding[0],kingslanding[1],new_board))
            {
                allmoves.append(M);
                allmaps.append(new_board);
            }
        }
    }
}

bool findallmovess::attacked(int px, int py, std::vector<std::vector<int>> map)
{
    int Enemy_Symbol;
    if(side) //what?
        Enemy_Symbol = 1;
    else
        Enemy_Symbol = -1;

    // check if can be attacked by knight;
    int x, y;
    if (px+1 < 8)
    {
        if (py+2 <8)
        {
            x = px+1;
            y = py+2;
            if (map[x][y]*Enemy_Symbol == 6)
            {
                return true;
            }
        }
        else if (py - 2 >=0)
        {
            x = px+1;
            y = py-2;
            if (map[x][y]*Enemy_Symbol == 6)
            {
                return true;
            }
        }
    }

    if (px-1 >= 0)
    {
        if (py+2 <8)
        {
            x = px-1;
            y = py+2;
            if (map[x][y]*Enemy_Symbol == 6)
            {
                return true;
            }
        }
        else if (py - 2 >=0)
        {
            x = px-1;
            y = py-2;
            if (map[x][y]*Enemy_Symbol == 6)
            {
                return true;
            }
        }
    }

    if (px+2 < 8)
    {
        if (py+1 <8)
        {
            x = px+2;
            y = py+1;
            if (map[x][y]*Enemy_Symbol == 6)
            {
                return true;
            }
        }
        else if (py - 1 >=0)
        {
            x = px+2;
            y = py-1;
            if (map[x][y]*Enemy_Symbol == 6)
            {
                return true;
            }
        }
    }

    if (px-2 >= 0)
    {
        if (py+1 <8)
        {
            x = px-2;
            y = py+1;
            if (map[x][y]*Enemy_Symbol == 6)
            {
                return true;
            }
        }
        else if (py - 1 >=0)
        {
            x = px-2;
            y = py-1;
            if (map[x][y]*Enemy_Symbol == 6)
            {
                return true;
            }
        }
    }

    // check for bishop and queen

    x = px +1;
    y = py +1;
    for (; x<8 && y <8;x++)
    {
        if (map[x][y] == 5*Enemy_Symbol || map[x][y] == 8*Enemy_Symbol )
        {
            return true;
        }
        else if (map[x][y] != 0)
        {
            break;
        }
        y++;
    }
    x = px +1;
    y = py -1;
    for (; x<8 && y >=0;x++)
    {
        if (map[x][y] == 5*Enemy_Symbol || map[x][y] == 8*Enemy_Symbol )
        {
            return true;
        }
        else if (map[x][y] != 0)
        {
            break;
        }
        y--;
    }
    x = px -1;
    y = py +1;
    for (; x>=0 && y <8;x--)
    {
        if (map[x][y] == 5*Enemy_Symbol || map[x][y] == 8*Enemy_Symbol )
        {
            return true;
        }
        else if (map[x][y] != 0)
        {
            break;
        }
        y++;
    }
    x = px -1;
    y = py -1;
    for (; x>=0 && y >=0; x--)
    {
        if (map[x][y] == 5*Enemy_Symbol || map[x][y] == 8*Enemy_Symbol )
        {
            return true;
        }
        else if (map[x][y] != 0)
        {
            break;
        }
        y--;
    }

    //rook&queen

    x = px +1;
    y = py;
    for (; x<8;x++)
    {
        if (map[x][y] == 7*Enemy_Symbol || map[x][y] == 8*Enemy_Symbol )
        {
            return true;
        }
        else if (map[x][y] != 0)
        {
            break;
        }
    }
    x = px -1;
    for (; x>=0;x--)
    {
        if (map[x][y] == 7*Enemy_Symbol || map[x][y] == 8*Enemy_Symbol )
        {
            return true;
        }
        else if (map[x][y] != 0)
        {
            break;
        }
    }
    x = px;
    y = py +1;
    for (; y<8;y++)
    {
        if (map[x][y] == 7*Enemy_Symbol || map[x][y] == 8*Enemy_Symbol )
        {
            return true;
        }
        else if (map[x][y] != 0)
        {
            break;
        }
    }
    y = py -1;
    for (; y>=0;y--)
    {
        if (map[x][y] == 7*Enemy_Symbol || map[x][y] == 8*Enemy_Symbol )
        {
            return true;
        }
        else if (map[x][y] != 0)
        {
            break;
        }
    }


    //king

    int Startx =px-1;
    int Starty =py-1;
    if (Startx < 0)
        Startx++;
    if (Starty < 0)
        Starty++;
    for (x = Startx; x < px+2 && x <8; x++)
    {
        for(y = Starty; y<py+2 && y <8;y++)
        {
                if (map[x][y] == 9*Enemy_Symbol)
                {
                    return true;
                }
        }
    }

    //pawn

    int pace = Enemy_Symbol;
    y = py + pace;
    if (y >0 && y<7)
    {
        x = px +1;
        if (x<8)
        {
            if (map[x][y] == 4*Enemy_Symbol)
                return true;
        }
        x = px -1;
        if (x >=0)
        {
            if (map[x][y] == 4*Enemy_Symbol)
                return true;
        }
    }


    return false;


}
