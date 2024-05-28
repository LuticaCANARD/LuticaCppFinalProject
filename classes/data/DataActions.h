#ifndef DATAACTIONS_H_
#define DATAACTIONS_H_

/**
 * @brief 
 * AI가 어디에 선택하는것이 좋을지를 결정해주기 위해서, 준비해주는 구조체.
 */
struct DataActions
{
    int x;
    int y;
    double score;
    DataActions(int _x, int _y, int _score) : x(_x), y(_y), score(_score) {}
};

#endif // DATAACTIONS_H_