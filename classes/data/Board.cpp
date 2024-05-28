#include "Pieces.h"
#include <iostream>
#include "Board.h"
using namespace std;
/**
 * @brief 보드를 정의함.
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
 * @brief board에 유저 혹은 컴퓨터의 말을 설정함.
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
 * 유저의 승리라면 1, 컴퓨터의 승리라면 -1, 진행중이면 0, 무승부라면 -2
 * @return int 
 */
int Board::getGameResult()
{
    // 가로
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
    // 세로
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
    // 대각 
    if(this->board[1][1] == NULL) return 0; // 중앙이 비어서, 승패를 판정할 수 없다. 진행중으로 return한다.
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
    
    // 추가배치가 가능하다면 진행중, 아니라면 무승부이다.
    // 추가로 배치가능한지를 조사하는 변수
    // 추가배치가 가능하면 True
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
