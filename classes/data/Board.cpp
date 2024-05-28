#include "Pieces.h"
#include <iostream>
#include "Board.h"
using namespace std;
/**
 * @brief ���带 ������.
 * 
 */

Board::Board(int size)
{
    this->size = size;
    this->board = new Pieces** [size];
    for(int a = 0 ; a < size ; a ++)
    {
        for (int b=0;b<size;b++)
        {
            this->board[a][b] = NULL;
        }
    }
}
Board::~Board()
{
    delete [] board;
}
void Board::print()
{
    for(int a = 0 ; a < this->size ; a ++)
    {
        if(a == 0) {
            cout << "--|";
            for(int b = 0 ; b < this->size ; b++)
            {
                cout << " " << (b+1) << " |";
            }
            cout << endl;
        }
        for (int b=0;b<this->size;b++)
        {
            if(b == 0) cout << (a+1) <<" |";
            
            char show = board[a][b] != NULL ? 
                (board[a][b]->getComputer() == true ? 'O' : 'X') 
                : ' ' ;
            cout << " " << show << " |" ;
        }
        cout << endl;
        cout << "--|";
        for(int b = 0 ; b < this->size ; b++)
        {
            cout << "---|";
        }
        cout << endl;
    }
}
/**
 * @brief board�� ���� Ȥ�� ��ǻ���� ���� ������.
 * 
 * @param _isComputer 
 * @param x 
 * @param y 
 * @return int 
 */
int Board::setInput(bool _isComputer,int x,int y)
{
    if(x < 0) 
        return -1;
    else if(x > 2) 
        return -2;
    else if(y < 0) 
        return -3;
    else if(y > 2) 
        return -4;

    int allocateX = x,allocateY = y;
    
    if(this->board[allocateX][allocateY] != NULL) 
        return -5;
    
    this->board[allocateX][allocateY] = new Pieces(_isComputer);
    return 1;
}
/**
 * @brief Get the Game Result object
 * ������ �¸���� 1, ��ǻ���� �¸���� -1, �������̸� 0, ���ºζ�� -2
 * @return int 
 */
int Board::getGameResult()
{
    // ����
    for (int r = 0; r < this->size ; r ++ ) 
    {
        if(this->board[r][0] == NULL) continue;
        bool computer = this->board[r][0]->getComputer();
        bool isFull = true;
        for(int c = 1 ; c < 3 ; c ++)
        {
            if(this->board[r][c] == NULL || this->board[r][c]->getComputer() != computer )
            {
                isFull = false;
                break;    
            }
        }
        if(isFull == true) return computer == true ? -1 : 1;
    }
    // ����
    for (int c = 0; c < this->size ; c ++ ) 
    {
        if(this->board[0][c] == NULL) continue;
        bool computer = this->board[0][c]->getComputer();
        bool isFull = true;
        for(int r = 1 ; r < 3 ; r ++)
        {
            if(this->board[r][c] == NULL || this->board[r][c]->getComputer() != computer )
            {
                isFull = false;
                break;    
            }
        }
        if(isFull == true) return computer == true ? -1 : 1;
    }
    // �밢 
    if(this->board[1][1] == NULL) return 0; // �߾��� ��, ���и� ������ �� ����. ���������� return�Ѵ�.
    bool computer = this->board[1][1]->getComputer();

    bool isFull = true;
    for(int a = 0; a < this->size ; a++ )
    {
        if( this->board[a][a] == NULL || this->board[a][a]->getComputer() != computer)
        {
            isFull = false;
            break;
        }
    }
    if(isFull == true) return computer == true ? -1 : 1;
    isFull = true;
    for(int a = 0; a < this->size ; a++ )
    {
        if(this->board[a][2-a] == NULL || this->board[a][2-a]->getComputer() != computer)
        {
            isFull = false;
            break;
        }
    }
    if(isFull == true) return computer == true ? -1 : 1;
    
    // �߰���ġ�� �����ϴٸ� ������, �ƴ϶�� ���º��̴�.
    // �߰��� ��ġ���������� �����ϴ� ����
    // �߰���ġ�� �����ϸ� True
    bool canSet = this->searchCanSetThisBoard() != 0;
    return canSet == true ? 0 : -2;
}

int Board::getWareCode(int r,int c)
{
    return this->board[r][c] == NULL ? 0 : 
        this->board[r][c]->getComputer() == true ? -1 : 1;
}
void Board::setWareSimulate(int r,int c, Pieces* target)
{
    this->board[r][c] = target;
}

int Board::searchCanSetThisBoard()
{
    int count = 0;
    for (int r = 0 ; r < this->size ; r ++)
    {
        for (int c=0 ; c < this->size ; c++) 
        {
            if(this->board[r][c] == NULL) 
            {
                count ++;
            }
        }
    }
    return count;
}
