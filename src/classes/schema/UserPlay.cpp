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
    cout << "������ ũ�⸦ �Է��ϼ��� : ";
    int size;
    cin >> size;
    this->board = new Board(size);
    ComPlay* complay = new ComPlay(board);
    BoardCheck* boardCheck = new BoardCheck(board,complay);
    cout << "Board size... : " << size << endl;
    this->computerFirst = computer_first;
    // ���� �ʱⰪ ����
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
    cout << "��ǥ�� �Է��ϼ���. (x,y) :";
    bool end = false;
    while (end == false){
        int x,y;
        scanf("(%d,%d)",&x,&y);
        // TODO : ������ ���ð����� ������ Ȯ���ؾ� ��.
        // setInput���� Ȯ���ϰ� �Ͽ���. 
        InputErrorCode code = this->board->setInput(false,x,y);
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
            cout << "�ٽ� �Է����ּ���." << endl;
        }
    }
}

void UserPlay::play()
{
    
}

// Path: classes/schema/UserPlay.h