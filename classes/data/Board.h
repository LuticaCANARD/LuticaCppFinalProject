#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"

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
public:
    Board(int _size); // �ʱ�ȭ��.
    ~Board(); // ��������.
    void print(); // ���带 �����.(�°�.)
    /**
     * @brief board�� ���� Ȥ�� ��ǻ���� �⹰�� ������.
     * 
     * @param _isComputer ��ǻ������ ����
     * @param x x��ǥ
     * @param y y��ǥ
     * @return int error code : 1�̸� ������. 
     */
    int setInput(bool _isComputer,int x,int y);
    /**
     * @brief Get the Game Result
     * @return int ������ �¸���� 1, ��ǻ���� �¸���� -1, �������̸� 0, ���ºζ�� -2
     */
    int getGameResult();
    /**
     * @brief �⹰�� �������� ��ȯ�մϴ�.
     * 1�� ����, -1�� ��ǻ��, 0�� �����Դϴ�.
     * @param x 
     * @param y 
     * @return int 
     */
    int getWareCode(int r,int c);
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


};

#endif // BOARD_H
// Path: classes/data/Board.cpp