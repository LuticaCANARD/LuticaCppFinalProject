#include <iostream>
#include "../data/Board.h"
#include "../data/Pieces.h"
#include "../../enums/PlayerGameResults.h"
#include "../../enums/PiecesCode.h"
#include "UserPlay.h"
#include "ComPlay.h"
#include "BoardCheck.h"
using namespace std;

UserPlay::UserPlay(bool computer_first)
{
    cout << "보드의 크기를 입력하세요 : ";
    int size;
    cin >> size;
    this->board = new Board(size);
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
    
}

// Path: classes/schema/UserPlay.h