#ifndef COMPLAY_H
#define COMPLAY_H
// TODO : �����ڸ� �°��Ѵ�.
// �°��, ��Ƽ�������� �ؽ��� ����Ͽ� ���� ����� �����Ѵ�.

#include "Board.h"

class ComPlay
{
private:
    Board* board;
    double predictSingle(Board* bd,int direct);// �������� ���� ������ 
    double** predictWeight; // ���� ����ġ
    int size; // ���� ����ġ ������ (���������� ����.)

public:
    ComPlay(Board* _board);
    ~ComPlay();
    double predict(); // ���� ������ ��ȯ
    double getPredictScore(int x, int y); // �ش� ��ǥ�� ���� ������ ��ȯ

};


#endif // COMPLAY_H
// Path: classes/schema/ComPlay.h