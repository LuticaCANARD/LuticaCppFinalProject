#ifndef GAMERESULT_H_
#define GAMERESULT_H_

struct GameResult
{
    int userScore;
    int computerScore;
    bool isGameEnd;
    GameResult(int _userScore, int _computerScore, bool _isGameEnd) : userScore(_userScore), computerScore(_computerScore), isGameEnd(_isGameEnd) {}
};

#endif // GAMERESULT_H_