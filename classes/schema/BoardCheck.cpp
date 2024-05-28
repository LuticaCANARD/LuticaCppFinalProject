#include "BoardCheck.h"
#include "Board.h"
#include "enums/PlayerGameResults.h"
#include "enums/PiecesCode.h"
#include <vector>
#include <map>
#include "ComPlay.h"
using namespace std;

BoardCheck::BoardCheck(Board* _board,ComPlay *_complay)
{
    this->board = _board;
    this->complay = _complay;
}
BoardCheck::~BoardCheck()
{
}
/**
 * @brief "게임 결과와는 상관하지 아니하고, " 사용자의 점수를 반환하는 함수
 * 
 * @return int 현 시점에서의 사용자의 점수
 */
int BoardCheck::getUserScore()
{
    PiecesCode** bd = this->board->getBoardInfo();
    int size = this->board->getSize();
    int result = 0;
    for(int a = 0 ; a < size ; a ++)
    {
        for (int b = 0;b < size; b ++)
        {
            if(bd[a][b] == PiecesCode::USER) result++; //  사용자의 기물이라면 점수를 증가시킴.
        }
    }
    return result;
}

/**
 * @brief "게임 결과와는 상관하지 아니하고, " 컴퓨터의 점수를 반환하는 함수
 * 
 * @return int 현 시점에서의 컴퓨터의 점수
 */
int BoardCheck::getComputerScore()
{
    PiecesCode** bd = this->board->getBoardInfo();
    int size = this->board->getSize();
    int result = 0;
    for(int a = 0 ; a < size ; a ++)
    {
        for (int b=0;b<size;b++)
        {
            if(bd[a][b] == PiecesCode::COMPUTER) result++; //  컴퓨터의 기물이라면 점수를 증가시킴.
        }
    }
    return result;
}

/**
 * @brief 게임 결과를 계산하는 함수
 * 
 */
PlayerGameResults BoardCheck::checkGameResult()
{
    /**
     * @brief 오셀로에서, 게임의 승패는 하기와 같이 결정된다.
     * 1. 일단 모든 칸이 채워졌을 때, 더 많은 기물을 가진 플레이어가 승리한다.
     * 2. 만약, 모든 플레이어가 더이상의 수를 둘 수 없을 때, 더 많은 기물을 가진 플레이어가 승리한다.
     * 3. 만약, 두 플레이어가 같은 수의 기물을 가지고 있다면, 무승부가 된다.
     * 
     */
    
}

/**
 * @brief 게임이 끝났는지 확인하는 함수
 * 
 * @return bool 게임이 끝났는지
 */
bool BoardCheck::isGameEnd()
{
    // 1. 모든 칸이 채워졌는지 확인
    PiecesCode** bd = this->board->getBoardInfo();
    int size = this->board->getSize();
    bool is_full = true;
    for(int a = 0 ; a < size ; a ++)
    {
        for (int b=0;b<size;b++)
        {
            if(bd[a][b] == PiecesCode::EMPTY) is_full = false;
        }
    }
    if(is_full == true) return true;
    // 2. 더이상의 수를 둘 수 있는지 확인

}
/**
 * @brief 둘 수 있는지만 조사.
 * 
 * @param computer 
 * @return vector<DataActions> 
 */
vector<DataActions> BoardCheck::getCanSetList(bool computer)
{
    vector<DataActions> result;
    PiecesCode** bd = this->board->getBoardInfo();
    int size = this->board->getSize();
    PiecesCode target = computer == true ? PiecesCode::COMPUTER : PiecesCode::USER;
    PiecesCode enemy = computer == true ? PiecesCode::USER : PiecesCode::COMPUTER;
    map<pair<int,int>,bool> checked = map<pair<int,int>,bool>();

    for(int a = 0 ; a < size ; a ++)
    {
        for (int b=0;b<size;b++)
        {
            if(bd[a][b] == target)
            {
                // 상하좌우 대각선을 조사
                for(int i = -1 ; i <= 1 ; i ++)
                {
                    for(int j = -1 ; j <= 1 ; j ++)
                    {
                        if(i == 0 && j == 0) continue; //자기자신이면 생략
                        int x = a + i;
                        int y = b + j;
                        if(x < 0 || x >= size || y < 0 || y >= size) continue; // 범위를 벗어나면 생략
                        if(bd[x][y] != PiecesCode::EMPTY) continue; // 이미 기물이 있으면 생략
                        if(checked.find(make_pair(x,y)) != checked.end()) continue; // 이미 조사한 곳이면 생략
                        checked[make_pair(x,y)] = true;
                        result.push_back(DataActions(x,y,this->complay->getPredictScore(x,y)));
                    }
                }
            }
        }
    }
    return result;
}
// Path: classes/schema/BoardCheck.cpp
