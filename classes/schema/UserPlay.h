#ifndef USERPLAY_H
#define USERPLAY_H
#include "Board.h"

class UserPlay
{
private:
    bool computerFirst;
    Board* board;
public:
    UserPlay(bool computer_first);
    ~UserPlay();
    void setInput();
};

#endif // USERPLAY_H
// Path: classes/schema/BoardCheck.h