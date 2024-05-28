#ifndef COMPLAY_H
#define COMPLAY_H
// TODO : 예언자를 승계한다.
// 승계시, 멀티스레딩과 해싱을 사용하여 성능 향상을 추진한다.

#include "Board.h"

class ComPlay
{
private:
    Board* board;
    double predictSingle(Board* bd,int direct);// 스레딩용 단일 예측자 
    double** predictWeight; // 예측 가중치
    int size; // 예측 가중치 사이즈 (보드사이즈와 같다.)

public:
    ComPlay(Board* _board);
    ~ComPlay();
    double predict(); // 예측 실행후 반환
    double getPredictScore(int x, int y); // 해당 좌표의 예측 점수를 반환

};


#endif // COMPLAY_H
// Path: classes/schema/ComPlay.h