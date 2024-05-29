#ifndef BOARDDRAW_H
#define BOARDDRAW_H

#include "../data/Board.h"
class BoardDraw
{
private:
    Board* board;
public:
    BoardDraw(Board* _board);
    ~BoardDraw();
    void draw();
};

#endif // BOARDDRAW_H
// Path: classes/schema/UserPlay.h