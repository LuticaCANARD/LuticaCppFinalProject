#include "BoardCheck.h"
#include "../data/Board.h"
#include "../../enums/PlayerGameResults.h"
#include "../../enums/PiecesCode.h"
#include <vector>
#include <map>
#include "ComPlay.h"
#include <iostream>

using namespace std;

BoardCheck::BoardCheck(Board* bd,ComPlay *mp){
    this->board = bd;
    this->complay = mp;
}
BoardCheck::~BoardCheck(){
}
/**
 * @brief "���� ����ʹ� ������� �ƴ��ϰ�, " ������� ������ ��ȯ�ϴ� �Լ�
 * 
 * @return int �� ���������� ������� ����
 */
int BoardCheck::getUserScore(){
    PiecesCode** bd = this->board->getBoardInfo();
    int size = this->board->getSize();
    int result = 0;
    for(int a = 0 ; a < size ; a ++)
    {
        for (int b = 0;b < size; b ++)
        {
            if(bd[a][b] == PiecesCode::USER) result++; //  ������� �⹰�̶�� ������ ������Ŵ.
        }
    }
    return result;
}

/**
 * @brief "���� ����ʹ� ������� �ƴ��ϰ�, " ��ǻ���� ������ ��ȯ�ϴ� �Լ�
 * 
 * @return int �� ���������� ��ǻ���� ����
 */
int BoardCheck::getComputerScore(){
    PiecesCode** bd = this->board->getBoardInfo();
    int size = this->board->getSize();
    int result = 0;
    for(int a = 0 ; a < size ; a ++)
    {
        for (int b=0;b<size;b++)
        {
            if(bd[a][b] == PiecesCode::COMPUTER) result++; //  ��ǻ���� �⹰�̶�� ������ ������Ŵ.
        }
    }
    return result;
}

/**
 * @brief ���� ����� ����ϴ� �Լ�
 * 
 */
PlayerGameResults BoardCheck::checkGameResult(){
    /**
     * @brief �����ο���, ������ ���д� �ϱ�� ���� �����ȴ�.
     * 1. �ϴ� ��� ĭ�� ä������ ��, �� ���� �⹰�� ���� �÷��̾ �¸��Ѵ�.
     * 2. ����, ��� �÷��̾ ���̻��� ���� �� �� ���� ��, �� ���� �⹰�� ���� �÷��̾ �¸��Ѵ�.
     * 3. ����, �� �÷��̾ ���� ���� �⹰�� ������ �ִٸ�, ���ºΰ� �ȴ�.
     * 
     */
    if(this->isGameEnd()){
        int user_score = this->getUserScore();
        int computer_score = this->getComputerScore();
        if(user_score > computer_score) return PlayerGameResults::WIN;
        else if(user_score < computer_score) return PlayerGameResults::LOSE;
        else return PlayerGameResults::DRAW;
    }
    return PlayerGameResults::PROGRESS;
}

/**
 * @brief ������ �������� Ȯ���ϴ� �Լ�
 * 
 * @return bool ������ ��������
 */
bool BoardCheck::isGameEnd(){
    // 1. ��� ĭ�� ä�������� Ȯ��
    std::cout<<(this->board)<<std::endl;
    PiecesCode** bd = this->board->getBoardInfo();
    std::cout<<".."<<std::endl;
    int size = this->board->getSize();
    bool is_full = true;
    for(int a = 0 ; a < size ; a ++){
        for (int b=0;b<size;b++){
            if(bd[a][b] == PiecesCode::EMPTY) is_full = false;
        }
    }
    if(is_full == true) return true;
    // 2. ���̻��� ���� �� �� �ִ��� Ȯ��
    vector<DataActions> can_set_list = getCanSetListOnBoard(this->board,true);
    if(can_set_list.size() == 0) return true;
    can_set_list = getCanSetListOnBoard(this->board,false);
    if(can_set_list.size() == 0) return true;
    return false;
}

vector<DataActions> BoardCheck::getCanSetListOnBoard(Board* _bd,bool computer){
    vector<DataActions> result;
    PiecesCode** bd = _bd->getBoardInfo();
    int size = _bd->getSize();
    PiecesCode target = computer == true ? PiecesCode::COMPUTER : PiecesCode::USER;
    PiecesCode enemy = computer == true ? PiecesCode::USER : PiecesCode::COMPUTER;
    map<pair<int,int>,bool> checked = map<pair<int,int>,bool>();

    for(int a = 0 ; a < size ; a ++){
        for (int b=0;b<size;b++){
            if(bd[a][b] == target){
                // �����¿� �밢���� ����
                for(int i = -1 ; i <= 1 ; i ++){
                    for(int j = -1 ; j <= 1 ; j ++){
                        if(i == 0 && j == 0) continue; //�ڱ��ڽ��̸� ����
                        int x = a + i;
                        int y = b + j;
                        if(x < 0 || x >= size || y < 0 || y >= size) continue; // ������ ����� ����
                        if(bd[x][y] != PiecesCode::EMPTY) continue; // �̹� �⹰�� ������ ����
                        if(checked.find(make_pair(x,y)) != checked.end()) continue; // �̹� ������ ���̸� ����
                        checked[make_pair(x,y)] = true;
                        result.push_back(DataActions(x,y,0));
                    }
                }
            }
        }
    }
    return result;
}
// Path: classes/schema/BoardCheck.cpp
