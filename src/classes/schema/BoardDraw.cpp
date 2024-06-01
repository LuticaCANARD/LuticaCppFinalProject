#include "BoardDraw.h"
#include "../data/Board.h"
#include <iostream>
#include <string>
using namespace std;

BoardDraw::BoardDraw(Board* _board)
{
    this->board = _board;
}

BoardDraw::~BoardDraw()
{
}

void BoardDraw::draw()
{
    PiecesCode** boardInfo = this->board->getBoardInfo();
    int size = this->board->getSize();
    for(int a = 0 ; a < size ; a ++)
    {
        if(a == 0) {
            cout << "---|";
            for(int b = 0 ; b < size ; b++)
            {
                if( b < 9 )
                    cout << " " << (b+1) << " |";
                else
                    cout << " " << (b+1) << "|";
            }
            cout << endl;
        }
        for (int b=0;b<size;b++)
        {
            if(b == 0) {
                if(a<9)
                    cout << " " << (a+1) << " |";
                else
                    cout << " " <<(a+1) <<"|";
            }
            
            char show = boardInfo[a][b] != PiecesCode::EMPTY ? 
                (boardInfo[a][b] == PiecesCode::COMPUTER ? 'O' : 'X') 
                : ' ' ;
            cout << " " << show << " |" ;
        }
        cout << endl;
        cout << "---|";
        for(int b = 0 ; b < size ; b++)
        {
            cout << "---|";
        }
        cout << endl;
    }
}
