#include "UserPlay.h"

#include <iostream>
#include "../data/Board.h"
#include "../data/Pieces.h"
#include "../../enums/PlayerGameResults.h"
#include "../../enums/PiecesCode.h"
#include "ComPlay.h"
#include "BoardCheck.h"
#include "../data/GameResult.h"
#include "BoardDraw.h"
using namespace std;

UserPlay::UserPlay(bool computer_first)
{
    cout << "������ ũ�⸦ �Է��ϼ��� : ";
    int size;
    cin >> size;

    Board* bod = new Board(size);
    this->board = bod;
    cout << "���带 �ʱ�ȭ�մϴ�.";
    ComPlay* lComplay = new ComPlay(bod);
    BoardCheck* lBoardCheck = new BoardCheck(bod,lComplay);
    this->boardDraw = new BoardDraw(bod);
    this->complay = lComplay;
    this->boardCheck = lBoardCheck;
    cout << "Board size... : " << size << endl;
    this->computerFirst = computer_first;
    // ���� �ʱⰪ ����
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
    cout << "���� �ʱ�ȭ �Ϸ�" << endl;
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
        cout << "��ǥ�� �Է��ϼ���. (x,y) :";
        int x,y;
        cin.ignore();
        scanf("(%d,%d)",&x,&y);
        // TODO : ������ ���ð����� ������ Ȯ���ؾ� ��.
        // setInput���� Ȯ���ϰ� �Ͽ���. 
        InputErrorCode code = this->board->setInput(false,y-1,x-1);
        switch(code)
        {
            case InputErrorCode::VALID_INPUT:
                cout << "������ �Է��� �Ϸ�Ǿ����ϴ�." << endl;
                end = true;
                break;
            case InputErrorCode::INVALID_INPUT_X_0:
                cout << "x��ǥ�� 0���� �۽��ϴ�." << endl;
                break;
            case InputErrorCode::INVALID_INPUT_X_MAX:
                cout << "x��ǥ�� �ִ밪�� �ʰ��մϴ�." << endl;
                break;
            case InputErrorCode::INVALID_INPUT_Y_0:
                cout << "y��ǥ�� 0���� �۽��ϴ�." << endl;
                break;
            case InputErrorCode::INVALID_INPUT_Y_MAX:
                cout << "y��ǥ�� �ִ밪�� �ʰ��մϴ�." << endl;
                break;
            case InputErrorCode::INVALID_INPUT_THERE_IS_ALREADY:
                cout << "�̹� �⹰�� �ֽ��ϴ�." << endl;
                break;
        }
        if(end == false)
        {
            cout << "�ٽ� �Է����ּ���.(x,y)" << endl;
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
        // ��ǻ�Ͱ� �����μ� ������ �����°�?
        if(this->boardCheck->isGameEnd())
        {
            return; // �����ٰ� �ǴܵǸ� ���⸮���Ѵ�.
        }
        this->setInput();
    }
    else
    {
        this->setInput();
        // ������ �����μ� ������ �����°�?
        if(this->boardCheck->isGameEnd())
        {
            return;
        }
        this->boardDraw->draw();

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
        return GameResult(0,0,false); // ������ ������ �ʾҴٸ� �� ����� ��ȯ�Ѵ�.
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