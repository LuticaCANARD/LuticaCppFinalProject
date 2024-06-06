#include "UserPlay.h"

#include <iostream>
#include "../data/Board.h"
#include "../data/Pieces.h"
#include "../data/GameResult.h"

#include "ComPlay.h"
#include "BoardCheck.h"
#include "BoardDraw.h"

#pragma region enums_include
#include "../../enums/PlayerGameResults.h"
#include "../../enums/PiecesCode.h"
#include "../../enums/GameState.h"
#pragma endregion enums_include

using namespace std;

UserPlay::UserPlay(bool computer_first)
{
    int size;
    do{
        cout << "보드의 크기를 입력하세요 : ";
        cin >> size;
        if(size < 6 || size > 12) cout << "6~12 사이의 값을 입력해주세요." << endl;
    }while(size < 6 || size > 12); // 6~12 사이의 값만 받는다.
    
    Board* bod = new Board(size);
    this->board = bod;
    cout << "보드를 초기화합니다.";
    ComPlay* lComplay = new ComPlay(bod);
    BoardCheck* lBoardCheck = new BoardCheck(bod,lComplay);
    this->boardDraw = new BoardDraw(bod);
    this->complay = lComplay;
    this->boardCheck = lBoardCheck;
    cout << "Board size... : " << size << endl;
    this->computerFirst = computer_first;
    // 이하 초기값 세팅
    if(this->computerFirst)
    {
        this->board->setInput(true,this->board->getSize()/2,this->board->getSize()/2,true);
        this->board->setInput(true,this->board->getSize()/2-1,this->board->getSize()/2-1,true);
        this->board->setInput(false,this->board->getSize()/2-1,this->board->getSize()/2,true);
        this->board->setInput(false,this->board->getSize()/2,this->board->getSize()/2-1,true);
    }
    else
    {
        this->board->setInput(false,this->board->getSize()/2,this->board->getSize()/2,true);
        this->board->setInput(false,this->board->getSize()/2-1,this->board->getSize()/2-1,true);
        this->board->setInput(true,this->board->getSize()/2-1,this->board->getSize()/2,true);
        this->board->setInput(true,this->board->getSize()/2,this->board->getSize()/2-1,true);
    }
    cout << "보드 초기화 완료" << endl;
}
UserPlay::~UserPlay()
{
    delete this->complay;
    delete this->boardCheck;
    delete this->board;
    delete this->boardDraw;
}

void UserPlay::setInput()
{
    bool end = false;
    while (end == false){
        this->boardDraw->draw();
        cout << "좌표를 입력하세요. (x,y) :";
        int x,y;
        cin.ignore();
        scanf("(%d,%d)",&x,&y);
        // TODO : 유저가 선택가능한 곳인지 확인해야 함.
        // setInput에서 확인하게 하였음. 
        InputErrorCode code = this->board->setInput(false,y-1,x-1);
        switch(code)
        {
            case InputErrorCode::VALID_INPUT:
                cout << "유저의 입력이 완료되었습니다." << endl;
                end = true; // 입력이 완료되었으므로 루프를 빠져나간다.
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
            case InputErrorCode::INVALID_INOUT_THERE_IS_NO_PIECE_TO_REVERSE:
                cout << "뒤집을 기물이 없습니다." << endl;
                break;
        }
        if(end == false)
        {
            cout << "다시 입력해주세요.(x,y)" << endl;
        }
    }
}

void UserPlay::play()
{

    // TODO...
    if(this->computerFirst)
    {

        if(this->boardCheck->isGameEnd() == GameState::PASS_USER_ONLY)
        {
            while(this->boardCheck->isGameEnd() != GameState::PASS_USER_ONLY)
            {
                this->boardDraw->draw();
                this->setInput();
            }
        }
        if(this->boardCheck->isGameEnd() != GameState::NONE)
        {
            DataActions computerAction = this->complay->predict();
            this->board->setInput(true,computerAction.x,computerAction.y);
        }
        // 컴퓨터가 둠으로서 게임이 끝났는가?
        if(this->boardCheck->isGameEnd() == GameState::NONE)
        {
            return; // 끝났다고 판단되면 조기리턴한다.
        } 
        else if(this->boardCheck->isGameEnd() == GameState::PASS_COMPUTER_ONLY)
        {
            // 컴퓨터가 둔 상태에서, 컴퓨터만 둘 수 있다면 유저의 턴은 생략한다. (그러나 게임은 끝나지 않았으므로 다시 돌아온다.)
            cout << "유저가 더이상 둘 수 있는 곳이 없습니다." << endl;
            return;
        }
        this->setInput();
    }
    else
    {
        if(this->boardCheck->isGameEnd() == GameState::PASS_COMPUTER_ONLY)
        {
            while(this->boardCheck->isGameEnd() != GameState::PASS_COMPUTER_ONLY)
            {
                DataActions computerAction = this->complay->predict();
                this->board->setInput(true,computerAction.x,computerAction.y);
            }
        }
        if(this->boardCheck->isGameEnd() != GameState::NONE) this->setInput();
        // 유저가 둠으로서 게임이 끝났는가?
        if(this->boardCheck->isGameEnd() == GameState::NONE)
        {
            return;
        }
        else if(this->boardCheck->isGameEnd() == GameState::PASS_USER_ONLY)
        {
            // 유저가 둔 상태에서, 유저만 둘 수 있다면 컴퓨터의 턴은 생략한다. (그러나 게임은 끝나지 않았으므로 다시 돌아온다.)
            cout << "컴퓨터가 더이상 둘 수 있는 곳이 없습니다." << endl;
            return;
        }
        this->boardDraw->draw();
        DataActions computerAction = this->complay->predict();
        this->board->setInput(true,computerAction.x,computerAction.y);
    }
}

bool UserPlay::getEnded()
{
    return this->boardCheck->isGameEnd() == GameState::NONE;
}

GameResult UserPlay::getGameResult()
{
    bool isGameEnd = this->boardCheck->isGameEnd() == GameState::NONE;
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
void UserPlay::showBoard()
{
    this->boardDraw->draw();
}

// Path: classes/schema/UserPlay.h