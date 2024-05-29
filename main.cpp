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
#include "src/classes/schema/BoardCheck.h"
#include "src/classes/schema/ComPlay.h"
#include "src/classes/schema/UserPlay.h"
#include "src/classes/schema/BoardDraw.h"
#include "src/classes/data/Board.h"
#include <string>
#include <iostream>

int main()
{
    cout <<"2017011 ���ؿ� C++ Final Project Othello Game" << endl;
    while(true)
    {
        UserPlay* userPlay = NULL;
        cout << "��ǻ���� �����̸� o�� �Է��ϼ��� : ";
        string c;
        getline(cin,c);
        if(c=="o"){
            userPlay = new UserPlay(true);
        } else {
            userPlay = new UserPlay(false);
        }
        // �ʱⰪ ������ �ϼ��Ͽ���. �׷��ٸ�, �����Ѵ�.

        // ������ ���������� ���� ������.
        while (userPlay->getEnded() == false) 
        {
            userPlay->play();
        }
        GameResult result = userPlay->getGameResult();
        cout << "������ �������ϴ�. " << endl;
        cout << "���� ��� : " << endl;
        cout << "������� ���� : " << result.userScore << endl;
        cout << "��ǻ���� ���� : " << result.computerScore << endl;
        cout << "������ ���� : ";
        if(result.userScore > result.computerScore)
        {
            cout << "�����" << endl;
        }
        else if(result.userScore < result.computerScore)
        {
            cout << "��ǻ��" << endl;
        }
        else
        {
            cout << "���º�" << endl;
        }
        delete userPlay; // ������ ������, userPlay�� �����Ѵ�.
        cout << "������ �ٽ� �����Ͻðڽ��ϱ�? (y/n) : ";
        string s;
        getline(cin,s);
        if(s=="n") break;
    }
    return 0;
}
