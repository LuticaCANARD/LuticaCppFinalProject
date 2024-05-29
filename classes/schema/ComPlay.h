#ifndef COMPLAY_H
#define COMPLAY_H
// TODO : �����ڸ� �°��Ѵ�.
// �°��, ��Ƽ�������� �ؽ��� ����Ͽ� ���� ����� �����Ѵ�.

#include "data/DataActions.h"
#include "Board.h"

class ComPlay
{
private:
    Board* board;
    DataActions predictSingle(Board* bd,int i,int j);// �������� ���� ������ 
    double** predictWeight; // ���� ����ġ
    int size; // ���� ����ġ ������ (���������� ����.)

public:
    ComPlay(Board* _board);
    ~ComPlay();
    DataActions predict(); // ���� ������ ��ȯ

};


#endif // COMPLAY_H
// Path: classes/schema/ComPlay.h