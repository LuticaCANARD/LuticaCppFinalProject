#include "BoardCheck.h"
#include "../data/Board.h"
#include "../../enums/PlayerGameResults.h"
#include "../../enums/PiecesCode.h"
#include "../../enums/GameState.h"
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
    if(this->isGameEnd() == GameState::NONE){
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
GameState BoardCheck::isGameEnd(){
    // 1. ��� ĭ�� ä�������� Ȯ��
    PiecesCode** bd = this->board->getBoardInfo();
    int size = this->board->getSize();
    bool is_full = true;
    cout << "size: " << size << endl;
    for(int a = 0 ; a < size ; a ++){
        for (int b=0;b<size;b++){
            if(bd[a][b] == PiecesCode::EMPTY) is_full = false;
        }
    }
    if(is_full == true) return GameState::NONE;
    // 2. ���̻��� ���� �� �� �ִ��� Ȯ��
    vector<DataActions> can_set_list_computer = getCanSetListOnBoard(this->board,true);
    vector<DataActions> can_set_list_user = getCanSetListOnBoard(this->board,false);
    #pragma region Debug
    cout << "can_set_list_computer: " << can_set_list_computer.size() << endl;
    cout << "can_set_list_user: " << can_set_list_user.size() << endl;
    #pragma endregion Debug
    if(can_set_list_computer.size() == 0 && can_set_list_user.size() == 0) return GameState::NONE;
    if(can_set_list_computer.size() == 0) return GameState::PASS_USER_ONLY;
    if(can_set_list_user.size() == 0) return GameState::PASS_COMPUTER_ONLY;
    return GameState::BOTH;
}

vector<DataActions> BoardCheck::getCanSetListOnBoard(Board* _bd,bool computer){
    vector<DataActions> result;
    PiecesCode** bd = _bd->getBoardInfo();
    int size = _bd->getSize();
    PiecesCode enemy = computer == true ? PiecesCode::USER : PiecesCode::COMPUTER;
    map<pair<int,int>,bool> checked = map<pair<int,int>,bool>();
    for(int a = 0 ; a < size ; a ++){
        for (int b=0;b<size;b++){
            if(bd[a][b] == enemy){
                // �����¿� �밢���� ����
                for(int i = -1 ; i <= 1 ; i ++){
                    for(int j = -1 ; j <= 1 ; j ++){
                        if(i == 0 && j == 0) continue; //�ڱ��ڽ��̸� ����
                        int x = a + i;
                        int y = b + j;
                        if(x < 0 || x > size-1 || y < 0 || y > size-1) continue; // ������ ����� ����
                        if(bd[x][y] != PiecesCode::EMPTY) continue; // �̹� �⹰�� ������ ����
                        if(checked.find(make_pair(x,y)) != checked.end()) continue; // �̹� ������ ���̸� ����
                        if(_bd->searchCanSetInThisPoint(x,y,computer)==false) continue; // �� �� ���� ���̸� ����
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
