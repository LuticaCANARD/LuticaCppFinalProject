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
        this->board[a] = new Pieces* [this->size];
        for (int b=0;b<this->size;b++)
        {
            if(_board.board[a][b] != NULL) this->board[a][b] = new Pieces(_board.board[a][b]); // 여기도 복사!
            else this->board[a][b] = NULL;
        }
    }
}

PiecesCode** Board::getBoardInfo()
{

    PiecesCode** result = new PiecesCode* [this->size];
    for(int a = 0 ; a < this->size ; a ++)
    {
        result[a] = new PiecesCode [this->size];
        for (int b=0;b<this->size;b++)
        {
            result[a][b] = this->board[a][b] == NULL ? PiecesCode::EMPTY : 
                this->board[a][b]->getComputer() == true ? PiecesCode::COMPUTER : PiecesCode::USER;
        }
    }
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
InputErrorCode Board::setInput(bool _isComputer,int x,int y,bool isInit)
{
    if(x < 0) 
        return InputErrorCode::INVALID_INPUT_X_0;
    else if(x > this->size) 
        return InputErrorCode::INVALID_INPUT_X_MAX;
    else if(y < 0) 
        return InputErrorCode::INVALID_INPUT_Y_0;
    else if(y > this->size) 
        return InputErrorCode::INVALID_INPUT_Y_MAX;

    int allocateX = x,allocateY = y;
    
    if(this->board[allocateX][allocateY] != NULL) 
        return InputErrorCode::INVALID_INPUT_THERE_IS_ALREADY;
    bool canSet = false;
    // If enemy is computer, then "enemy" is user. so value is false.
    // If enemy is user, then "enemy" is computer. so value is true.
    if(isInit == false && this->searchCanSetInThisPoint(allocateX,allocateY,_isComputer) == false) {
        return InputErrorCode::INVALID_INOUT_THERE_IS_NO_PIECE_TO_REVERSE;
    }

    this->board[allocateX][allocateY] = new Pieces(_isComputer);

    this->updateBoard(allocateX,allocateY,_isComputer);

    return InputErrorCode::VALID_INPUT;
}
InputErrorCode Board::setInput(bool _isComputer,int x,int y)
{
    return this->setInput(_isComputer,x,y,false);
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
                if(fx < 0 || fx > this->size-1 || fy < 0 || fy > this->size-1) break;
                if(this->board[fx][fy] == NULL) break;
                if(isComputer != this->board[fx][fy]->getComputer()) continue;
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
                    if(fx < 0 || fx > this->size-1 || fy < 0 || fy > this->size-1) break;
                    if(this->board[fx][fy] == NULL) break;
                    if(isComputer != this->board[fx][fy]->getComputer()) {
                        this->board[fx][fy]->reverse();
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

bool Board::searchCanSetInThisPoint(int x,int y,bool isComputer)
{
    if(this->board[x][y] != NULL) return false;
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
                if(fx < 0 || fx > this->size-1 || fy < 0 || fy > this->size-1) break;
                if(this->board[fx][fy] == NULL) break;
                if(this->board[fx][fy]->getComputer() != isComputer) {
                    catchingEnemy = true;
                    continue;
                } else if (this->board[fx][fy]->getComputer() == isComputer && catchingEnemy == true ) {
                    return true; // 최소 1회이상 조우하였으므로 둘 수 있음.
                } else if (this->board[fx][fy]->getComputer() == isComputer) break; // 조우한 바 없으므로 둘 수 없음.
                
            }
        }
    }
    return false;
}

int Board::searchCanSetThisBoardCount(int x,int y,bool isComputer)
{
    int result = 0;
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
                if(fx < 0 || fx > this->size-1 || fy < 0 || fy > this->size-1) break;
                if(this->board[fx][fy] == NULL) break;
                if(this->board[fx][fy]->getComputer() != isComputer) {
                    catchingEnemy = true;
                    continue;
                } else if (this->board[fx][fy]->getComputer() == isComputer && catchingEnemy == true ) {
                    return true; // 최소 1회이상 조우하였으므로 둘 수 있음.
                } else if (this->board[fx][fy]->getComputer() == isComputer) break; // 조우한 바 없으므로 둘 수 없음.
            }
            if(catchingEnemy == true){
                while(true)
                {
                    fx -= i;
                    fy -= j;
                    if(x==fx && y==fy) break;
                    if(fx < 0 || fx >= this->size-1 || fy < 0 || fy >= this->size-1) break;
                    if(this->board[fx][fy] == NULL) break;
                    if(this->board[fx][fy]->getComputer() != isComputer) {
                        result++;
                    } else if(this->board[fx][fy]->getComputer() == isComputer) {
                        break;
                    }
                }
            }
        }
    }
    return result;
}
int Board::getSize()
{
    return this->size;
}
