#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"
#include "PlayerGameResults.h"
#include "PiecesCode.h"
#include "enums/InputErrorCode.h"

using namespace std;
/**
 * @brief ���带 ������.
 * (Board�� �°��Ͽ� N���� Ȯ���� �� �ְ� ��.)
 */

class Board
{
private:
    Pieces *** board; // ���� �������� ������ ���� ũ�� �迭 �Ҵ��� ���Ͽ� ����ϴ� ����.
    // ����...
    int size; // ������ ũ��. 
    bool _flag_changed_board_before_get_code; // ���尡 ����Ǿ����� ���θ� ��Ÿ��.
    PiecesCode** _board_cache; // ������ ������ ĳ�̵�.
public:
    Board(int _size); // �ʱ�ȭ��.
    ~Board(); // ��������.
    PiecesCode** getBoardInfo(); // ���� ������ ������(print ��ü. ����-��� ��Ģ)
    /**
     * @brief board�� ���� Ȥ�� ��ǻ���� �⹰�� ������.
     * 
     * @param _isComputer ��ǻ������ ����
     * @param x x��ǥ
     * @param y y��ǥ
     * @return int error code : 1�̸� ������. 
     */
    InputErrorCode setInput(bool _isComputer,int x,int y);
    /**
     * @brief �⹰�� �������� ��ȯ�մϴ�.
     * 1�� ����, -1�� ��ǻ��, 0�� �����Դϴ�.
     * @param x 
     * @param y 
     * @return PiecesCode  
     */
    PiecesCode getWareCode(int r,int c);
    /**
     * @brief �� ���忡 "������" �⹰�� ��ġ�մϴ�.
     * 
     * @param r y��ǥ
     * @param c x��ǥ
     * @param target ��ġ�� �⹰�Դϴ�. 
     */
    void setWareSimulate(int r,int c, Pieces* target);
    /**
     * @brief �� ���忡 �߰��� �⹰�� �� �� �ִ��� Ȯ���մϴ�. 
     * 
     * @return int �߰��� ��ġ ������ �⹰�� ���Դϴ�.
     */
    int searchCanSetThisBoard();
    int getSize(); // ������ ũ�⸦ ��ȯ��.
};

#endif // BOARD_H
// Path: classes/data/Board.cpp