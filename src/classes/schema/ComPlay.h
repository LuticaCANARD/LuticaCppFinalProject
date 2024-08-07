#ifndef COMPLAY_H
#define COMPLAY_H
// TODO : 예언자를 승계한다.
// 승계시, 멀티스레딩과 해싱을 사용하여 성능 향상을 추진한다.

#include "../data/DataActions.h"
#include "../data/Board.h"

class ComPlay
{
private:
    Board* board;
    DataActions predictSingle(Board* bd,int i,int j);// 스레딩용 단일 예측자 
    double** predictWeight; // 예측 가중치
    int size; // 예측 가중치 사이즈 (보드사이즈와 같다.)

public:
    ComPlay(Board* _board);
    ~ComPlay();
    DataActions predict(); // 예측 실행후 반환

};


#endif // COMPLAY_H
// Path: classes/schema/ComPlay.h