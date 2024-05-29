#ifndef BOARDCHECK_H
#define BOARDCHECK_H

#include "../data/Board.h"
#include "../../enums/PlayerGameResults.h"
#include "../data/DataActions.h"
#include "ComPlay.h"
#include <vector>
using namespace std;
class BoardCheck
{
private:
    Board* board;
    ComPlay* complay;

public:
    BoardCheck(Board* _board,ComPlay *_complay);
    ~BoardCheck();

    int getUserScore();
    int getComputerScore();

    PlayerGameResults checkGameResult();
    bool isGameEnd();
    
    static vector<DataActions> getCanSetListOnBoard(Board* _bd,bool computer);

};


#endif // BOARDCHECK_H
// Path: classes/schema/BoardCheck.h