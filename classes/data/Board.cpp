#include "Pieces.h"
#include <iostream>
#include "Board.h"
#include "PlayerGameResults.h"
#include "PiecesCode.h"
#include "enums/InputErrorCode.h"

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
    for (int a = 0 ; a < this->size ; a ++)
    {
        delete [] this->board[a];
    }
    delete [] board;
}


PiecesCode** Board::getBoardInfo()
{
    if(this->_flag_changed_board_before_get_code == false) 
        return this->_board_cache;
    PiecesCode** result = new PiecesCode* [this->size];
    for(int a = 0 ; a < this->size ; a ++)
    {
        for (int b=0;b<this->size;b++)
        {
            result[a][b] = this->board[a][b] == NULL ? PiecesCode::EMPTY : 
                this->board[a][b]->getComputer() == true ? PiecesCode::COMPUTER : PiecesCode::USER;
        }
    }
    this->_board_cache = result;
    return result;
}
/**
 * @brief board에 유저 혹은 컴퓨터의 말을 설정함.
 * 
 * @param _isComputer 
 * @param x 
 * @param y 
 * @return int 
 */
InputErrorCode Board::setInput(bool _isComputer,int x,int y)
{
    if(x < 0) 
        return InputErrorCode::INVALID_INPUT_X_0;
    else if(x > this->size - 1) 
        return InputErrorCode::INVALID_INPUT_X_MAX;
    else if(y < 0) 
        return InputErrorCode::INVALID_INPUT_Y_0;
    else if(y > this->size - 1) 
        return InputErrorCode::INVALID_INPUT_Y_MAX;

    int allocateX = x,allocateY = y;
    
    if(this->board[allocateX][allocateY] != NULL) 
        return InputErrorCode::INVALID_INPUT_THERE_IS_ALREADY;
    
    this->_flag_changed_board_before_get_code = true;
    delete this->_board_cache;
    this->board[allocateX][allocateY] = new Pieces(_isComputer);
    return InputErrorCode::VALID_INPUT;
}

PiecesCode Board::getWareCode(int r,int c)
{
    return this->board[r][c] == NULL ? PiecesCode::EMPTY : 
        this->board[r][c]->getComputer() == true ? PiecesCode::COMPUTER : PiecesCode::USER;
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
        for (int c = 0 ; c < this->size ; c++) 
        {
            if(this->board[r][c] == NULL) 
            {
                count ++;
            }
        }
    }
    return count;
}
int Board::getSize()
{
    return this->size;
}
