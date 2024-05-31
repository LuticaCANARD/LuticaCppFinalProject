#ifndef USERPLAY_H
#define USERPLAY_H
#include "../data/Board.h"
#include "ComPlay.h"
#include "../data/GameResult.h"
#include "BoardCheck.h"
#include "BoardDraw.h"
class UserPlay
{
private:
    bool computerFirst;
    Board* board;
    ComPlay* complay;
    BoardCheck* boardCheck;
    BoardDraw* boardDraw;
public:
    UserPlay(bool computer_first);
    ~UserPlay();
    void setInput();
    void play();
    bool getEnded();
    void showBoard();
    GameResult getGameResult();
};

#endif // USERPLAY_H
// Path: classes/schema/UserPlay.cpp