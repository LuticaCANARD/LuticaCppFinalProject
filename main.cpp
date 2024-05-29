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
        cout << "보드 크기를 정하세요" << endl;
        int size;
        cin >> size;
        Board* board = new Board(size);
        UserPlay* userPlay = NULL;
        cout << "컴퓨터의 선공이면 o를 입력하세요 : ";
        string c;
        getline(cin,c);
        if(c=="o"){
            userPlay = new UserPlay(true);
        } else {
            userPlay = new UserPlay(false);
        }
        
        
    }
    return 0;
}
