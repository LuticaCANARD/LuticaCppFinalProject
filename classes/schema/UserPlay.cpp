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
    int x,y;
    scanf("(%d,%d)",&x,&y);
    this->board->setInput(false,x,y);
}

// Path: classes/schema/UserPlay.h