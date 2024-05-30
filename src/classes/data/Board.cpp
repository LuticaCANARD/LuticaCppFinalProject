#include "Board.h"
#include "Pieces.h"
#include <iostream>
#include "../../enums/PlayerGameResults.h"
#include "../../enums/PiecesCode.h"
#include "../../enums/InputErrorCode.h"
#include <vector>
#include "../data/DataActions.h"
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
        this->board[a] = new Pieces* [size];
        for (int b=0;b<size;b++)
        {
            this->board[a][b] = NULL;
        }
    }
    this->_flag_changed_board_before_get_code = true;
    this->_board_cache = NULL;
}
Board::~Board()
{
    for (int a = 0 ; a < this->size ; a ++)
    {
        delete [] this->board[a];
    }
    delete [] board;
}
Board::Board(const Board& _board)
{
    // 이것은 깊은 복사문제로 인하여 발생함.
    this->size = _board.size;
    this->board = new Pieces** [this->size];
    for(int a = 0 ; a < this->size ; a ++)
    {
        for (int b=0;b<this->size;b++)
        {
            this->board[a][b] = _board.board[a][b];
        }
    }
}

PiecesCode** Board::getBoardInfo()
{
    std::cout<<".."<<std::endl;

    if(this->_flag_changed_board_before_get_code == false) 
        return this->_board_cache;
    PiecesCode** result = new PiecesCode* [this->size];
    for(int a = 0 ; a < this->size ; a ++)
    {
        std::cout<<".."<<std::endl;

        result[a] = new PiecesCode [this->size];
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
    if(this->_board_cache != NULL)
    {
        for(int a = 0 ; a < this->size ; a ++)
        {
            delete [] this->_board_cache[a];
        }
        delete [] this->_board_cache;
        this->_board_cache = nullptr;
    }
    this->board[allocateX][allocateY] = new Pieces(_isComputer);

    this->updateBoard(allocateX,allocateY,_isComputer);

    return InputErrorCode::VALID_INPUT;
}

void Board::updateBoard(int x,int y,bool isComputer)
{
    for (int i=-1;i<=1;i++){
        for (int j=-1;j<=1;j++)
        {
            
            if(i == 0 && j == 0) continue;
            bool catchingEnemy = false;
            int fx = x,fy = y;
            while(true)
            {
                fx += i;
                fy += j;
                if(x < 0 || x >= this->size || y < 0 || y >= this->size) break;
                if(this->board[x][y] == NULL) break;
                if(isComputer == false && this->board[x][y]->getComputer() == true) continue;
                else if(isComputer == true && this->board[x][y]->getComputer() == false) continue;
                else 
                {
                    catchingEnemy = true;
                    break;
                }
            }
            if(catchingEnemy == true){
                while(true)
                {
                    fx -= i;
                    fy -= j;
                    if(x==fx && y==fy) break;
                    if(x < 0 || x >= this->size || y < 0 || y >= this->size) break;
                    if(this->board[x][y] == NULL) break;
                    if(isComputer == false && this->board[x][y]->getComputer() == true) {
                        this->board[x][y]->reverse();
                    } else if(isComputer == true && this->board[x][y]->getComputer() == false) {
                        this->board[x][y]->reverse();
                    }
                    else break;
                }
            }
        }
    }
}

PiecesCode Board::getPieceCode(int r,int c)
{
    return this->board[r][c] == NULL ? PiecesCode::EMPTY : 
        this->board[r][c]->getComputer() == true ? PiecesCode::COMPUTER : PiecesCode::USER;
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
