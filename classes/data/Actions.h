#ifndef DATAACTIONS_H_
#define DATAACTIONS_H_

/**
 * @brief 
 * AI�� ��� �����ϴ°��� �������� �������ֱ� ���ؼ�, �غ����ִ� ����ü.
 */
struct DataActions
{
    int x;
    int y;
    double score;
    DataActions(int _x, int _y, int _score) : x(_x), y(_y), score(_score) {}
};

#endif // DATAACTIONS_H_