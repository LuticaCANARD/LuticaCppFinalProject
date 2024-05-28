#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"
#include "PlayerGameResults.h"
#include "PiecesCode.h"
#include "enums/InputErrorCode.h"

using namespace std;
/**
 * @brief 보드를 정의함.
 * (Board를 승계하여 N으로 확장할 수 있게 함.)
 */

class Board
{
private:
    Pieces *** board; // 삼중 포인터인 이유는 동적 크기 배열 할당을 위하여 사용하는 것임.
    // 삼중...
    int size; // 보드의 크기. 
    bool _flag_changed_board_before_get_code; // 보드가 변경되었는지 여부를 나타냄.
    PiecesCode** _board_cache; // 보드의 정보가 캐싱됨.
public:
    Board(int _size); // 초기화임.
    ~Board(); // 삭제자임.
    PiecesCode** getBoardInfo(); // 보드 정보를 가져옴(print 대체. 개방-폐쇄 원칙)
    /**
     * @brief board에 유저 혹은 컴퓨터의 기물을 설정함.
     * 
     * @param _isComputer 컴퓨터인지 여부
     * @param x x좌표
     * @param y y좌표
     * @return int error code : 1이면 정상임. 
     */
    InputErrorCode setInput(bool _isComputer,int x,int y);
    /**
     * @brief Get the Game Result
     * @return PlayerGameResults 유저의 승리라면 1, 컴퓨터의 승리라면 -1, 진행중이면 0, 무승부라면 -2
     */
    PlayerGameResults getGameResult();
    /**
     * @brief 기물의 소유권을 반환합니다.
     * 1은 유저, -1은 컴퓨터, 0은 없음입니다.
     * @param x 
     * @param y 
     * @return PiecesCode  
     */
    PiecesCode getWareCode(int r,int c);
    /**
     * @brief 이 보드에 "가상의" 기물을 설치합니다.
     * 
     * @param r y좌표
     * @param c x좌표
     * @param target 설치할 기물입니다. 
     */
    void setWareSimulate(int r,int c, Pieces* target);
    /**
     * @brief 이 보드에 추가로 기물을 둘 수 있는지 확인합니다. 
     * 
     * @return int 추가로 배치 가능한 기물의 수입니다.
     */
    int searchCanSetThisBoard();
    int getSize(); // 보드의 크기를 반환함.
};

#endif // BOARD_H
// Path: classes/data/Board.cpp