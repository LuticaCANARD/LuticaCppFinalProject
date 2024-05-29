#include <iostream>
#include "data/Board.h"
#include "data/Pieces.h"
#include "enums/PlayerGameResults.h"
#include "enums/PiecesCode.h"
#include "UserPlay.h"

using namespace std;

UserPlay::UserPlay(bool computer_first)
{
    cout << "������ ũ�⸦ �Է��ϼ��� : ";
    int size;
    cin >> size;
    this->board = new Board(size);
    cout << "Board size... : " << size << endl;
    this->computerFirst = computer_first;
    // ���� �ʱⰪ ����
    if(this->computerFirst)
    {
        this->board->setInput(true,0,0);
    }
    else
    {
        this->board->setInput(false,0,0);
    }
}
UserPlay::~UserPlay()
{
    delete this->board;
}

void UserPlay::setInput()
{
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
    }
}

// Path: classes/schema/UserPlay.h