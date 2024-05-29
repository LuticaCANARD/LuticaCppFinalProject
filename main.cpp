/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "classes/schema/BoardCheck.h"
#include "classes/schema/ComPlay.h"
#include "classes/schema/UserPlay.h"
#include "classes/schema/BoardDraw.h"
#include "classes/data/Board.h"

#include <iostream>

int main()
{
    cout <<"2017011 이준영 C++ Final Project Othello Game" << endl;
    while(true)
    {
        UserPlay* userPlay = NULL;
        cout << "컴퓨터의 선공이면 o를 입력하세요 : ";
        string c;
        getline(cin,c);
        if(c=="o"){
            userPlay = new UserPlay(true);
        } else {
            userPlay = new UserPlay(false);
        }
        // 초기값 셋팅을 완수하였다. 그렇다면, 진행한다.

        // 게임이 끝날때까지 턴을 돌린다.
        while (userPlay->getEnded() == false) 
        {
            userPlay->play();
        }
        GameResult result = userPlay->getGameResult();
        cout << "게임이 끝났습니다. " << endl;
        cout << "게임 결과 : " << endl;
        cout << "사용자의 점수 : " << result.userScore << endl;
        cout << "컴퓨터의 점수 : " << result.computerScore << endl;
        cout << "게임의 승자 : ";
        if(result.userScore > result.computerScore)
        {
            cout << "사용자" << endl;
        }
        else if(result.userScore < result.computerScore)
        {
            cout << "컴퓨터" << endl;
        }
        else
        {
            cout << "무승부" << endl;
        }
        delete userPlay; // 게임이 끝나면, userPlay를 삭제한다.
        cout << "게임을 다시 시작하시겠습니까? (y/n) : ";
        string s;
        getline(cin,s);
        if(s=="n") break;
    }
    return 0;
}
