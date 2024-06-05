#include "ComPlay.h"
#include <thread>
#include <mutex>
#include <vector>
#include <future>
#include "../data/DataActions.h"
#include "algorithm"
#include <iostream>
#include "BoardCheck.h"

ComPlay::ComPlay(Board* _board)
{
    board = _board;
    size = board->getSize();
    predictWeight = new double*[size];
    for (int i = 0; i < size; i++)
    {
        predictWeight[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            if(j==0 || j==size-1 || i==0 || i==size-1){
                if( (i==0 && j==0) || (i==0 && j==size-1) || (i==size-1 && j==0) || (i==size-1 && j==size-1) )
                    predictWeight[i][j] = 1000;
                else if(i==1 || j == 1 || i == size-2 || j == size-2)
                    predictWeight[i][j] = 1;
                else 
                    predictWeight[i][j] = 10;
            }
            else
            {
                if((i == 1 && j == 1) || (i==size-2 && j== 1) || ( i == 1 && j == size - 2 ) || (i == size-2 && j == size-2))
                    predictWeight[i][j] = 1;
                else
                    predictWeight[i][j] = 5;
            }
        }
    }
}

ComPlay::~ComPlay()
{
    for (int i = 0; i < size; i++)
    {
        delete[] predictWeight[i];
    }
    delete[] predictWeight;
}
/**
 * @brief Ȯ������ �����Ѵ�.
 * 
 * @param bd 
 * @param i 
 * @param j 
 * @return double 
 */
DataActions ComPlay::predictSingle(Board* bd, int i,int j)
{
    /**
     * @brief �������, �� �Լ��� ��� ����� ���� ������ �ϳ�, ����Լ� ȣ��� �ʹ� ���� ������ �ϰ� �� ������ ���̰�, �䱸���׿��� Heuristic�� ����� �ֹ��� ��, �׳� 1������ �ùķ��̼��� ����� greedy�ϰ� �ݿ��ϰ� �Ѵ�. ��.
     */

    if(i < 0 || i >= size-1 || j < 0 || j >= size-1)
        return DataActions(i,j,-99);
    if(bd->getBoardInfo()[i][j] != PiecesCode::EMPTY)
        return DataActions(i,j,-99); // �ű� ����.
    Board simulator = Board(*bd); // �������� ����.
    // �ϴ� �־��� �ó������� �ùķ��̼� �Ѵ�.
    simulator.setInput(true,i,j);
    int result = 0;
    for(int x=0;x<size;x++)
    {
        for(int y=0;y<size;y++)
        {
            if(simulator.getPieceCode(x,y) == PiecesCode::COMPUTER)
            {
                simulator.setInput(false,x,y);
            }
        }
    }
    for(int x=0;x<size;x++)
    {
        for(int y=0;y<size;y++)
        {
            if(simulator.getPieceCode(x,y) == PiecesCode::COMPUTER)
            {
                result += predictWeight[x][y];
            }
        }
    }
    //delete simulator; // auto value�̴�. �����ʿ����.
    // Weight + ������ (������ == ������ delta�� ���� ȿ���̹Ƿ�.)
    return DataActions(i,j,predictWeight[i][j] + result); 
}
DataActions ComPlay::predict()
{
    vector<DataActions> canAction = BoardCheck::getCanSetListOnBoard(board,true);
    vector<future<DataActions>> futures;
    futures.reserve(canAction.size());
    double max = 0;
    int x = -1;
    int y = -1;
    for(int i = 0; i < canAction.size(); i++)
    {
        futures.emplace_back(async(launch::async,&ComPlay::predictSingle,this,board,canAction[i].x,canAction[i].y));
    }
    for(auto& f : futures)
    {
        DataActions da = f.get();
        if(da.score > max)
        {
            max = da.score;
            x = da.x;
            y = da.y;
        }
    }
    return DataActions(x,y,max);
}

