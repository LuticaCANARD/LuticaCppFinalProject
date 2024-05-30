#include "UserPlay.h"

#include <iostream>
#include "../data/Board.h"
#include "../data/Pieces.h"
#include "../../enums/PlayerGameResults.h"
#include "../../enums/PiecesCode.h"
#include "ComPlay.h"
#include "BoardCheck.h"
#include "../data/GameResult.h"
using namespace std;

UserPlay::UserPlay(bool computer_first)
{
    cout << "보드의 크기를 입력하세요 : ";
    int size;
    cin >> size;
    this->board = new Board(size);
    cout << "보드를 초기화합니다.";
    ComPlay* complay = new ComPlay(board);
    BoardCheck* boardCheck = new BoardCheck(board,complay);
    cout << "Board size... : " << size << endl;
    this->computerFirst = computer_first;
    // 이하 초기값 세팅
    if(this->computerFirst)
    {
        this->board->setInput(true,this->board->getSize()/2,this->board->getSize()/2);
        this->board->setInput(true,this->board->getSize()/2+1,this->board->getSize()/2+1);
        this->board->setInput(false,this->board->getSize()/2+1,this->board->getSize()/2);
        this->board->setInput(false,this->board->getSize()/2,this->board->getSize()/2+1);
    }
    else
    {
        this->board->setInput(false,this->board->getSize()/2,this->board->getSize()/2);
        this->board->setInput(false,this->board->getSize()/2+1,this->board->getSize()/2+1);
        this->board->setInput(true,this->board->getSize()/2+1,this->board->getSize()/2);
        this->board->setInput(true,this->board->getSize()/2,this->board->getSize()/2+1);
    }
    cout << "보드 초기화 완료" << endl;
}
UserPlay::~UserPlay()
{
    delete this->complay;
    delete this->boardCheck;
    delete this->board;
}

void UserPlay::setInput()
{
    cout << "좌표를 입력하세요. (x,y) :";
    bool end = false;
    while (end == false){
        int x,y;
        scanf("(%d,%d)",&x,&y);
        // TODO : 유저가 선택가능한 곳인지 확인해야 함.
        // setInput에서 확인하게 하였음. 
        InputErrorCode code = this->board->setInput(false,x,y);
        switch(code)
        {
            case InputErrorCode::VALID_INPUT:
                cout << "유저의 입력이 완료되었습니다." << endl;
                end = true;
                break;
            case InputErrorCode::INVALID_INPUT_X_0:
                cout << "x좌표가 0보다 작습니다." << endl;
                break;
            case InputErrorCode::INVALID_INPUT_X_MAX:
                cout << "x좌표가 최대값을 초과합니다." << endl;
                break;
            case InputErrorCode::INVALID_INPUT_Y_0:
                cout << "y좌표가 0보다 작습니다." << endl;
                break;
            case InputErrorCode::INVALID_INPUT_Y_MAX:
                cout << "y좌표가 최대값을 초과합니다." << endl;
                break;
            case InputErrorCode::INVALID_INPUT_THERE_IS_ALREADY:
                cout << "이미 기물이 있습니다." << endl;
                break;
        }
        if(end == false)
        {
            cout << "다시 입력해주세요." << endl;
        }
    }
}

void UserPlay::play()
{
    // TODO...
    if(this->computerFirst)
    {
        DataActions computerAction = this->complay->predict();
        this->board->setInput(true,computerAction.x,computerAction.y);
        // 컴퓨터가 둠으로서 게임이 끝났는가?
        if(this->boardCheck->isGameEnd())
        {
            return; // 끝났다고 판단되면 조기리턴한다.
        }
        this->setInput();
    }
    else
    {
        this->setInput();
        // 유저가 둠으로서 게임이 끝났는가?
        if(this->boardCheck->isGameEnd())
        {
            return;
        }
        DataActions computerAction = this->complay->predict();
        this->board->setInput(true,computerAction.x,computerAction.y);
    }
}

bool UserPlay::getEnded()
{
    return this->boardCheck->isGameEnd();
}

GameResult UserPlay::getGameResult()
{
    bool isGameEnd = this->boardCheck->isGameEnd();
    if(isGameEnd == false) 
    {
        return GameResult(0,0,false); // 게임이 끝나지 않았다면 빈 결과를 반환한다.
    }
    PiecesCode** bd = this->board->getBoardInfo();
    int size = this->board->getSize();
    int userScore = 0;
    int computerScore = 0;
    for (int a = 0; a < size ; a++) 
    {
        for (int b = 0; b < size ; b++)
        {
            if(bd[a][b] == PiecesCode::USER) userScore++;
            else if(bd[a][b] == PiecesCode::COMPUTER) computerScore++;
            else if(bd[a][b] == PiecesCode::EMPTY) continue;
        }
    }
    return GameResult(userScore,computerScore,isGameEnd);
}

// Path: classes/schema/UserPlay.h