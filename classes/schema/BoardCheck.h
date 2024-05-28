#ifndef BOARDCHECK_H
#define BOARDCHECK_H

class BoardCheck
{
private:
    int userScore;
    int computerScore;

public:
    BoardCheck();
    ~BoardCheck();

    int getUserScore();
    int getComputerScore();

    void calculateScore();
};

#endif // BOARDCHECK_H
// Path: classes/schema/BoardDraw.h