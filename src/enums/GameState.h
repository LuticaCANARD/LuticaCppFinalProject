#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GameState // �� ������ ���¸� �ǹ��Ѵ�.
{
    BOTH=1, // �� �� �� �� �ִ�.
    PASS_USER_ONLY=2, // ����ڸ� �� �� �ִ�.
    PASS_COMPUTER_ONLY=3, // ��ǻ�͸� �� �� �ִ�.
    NONE=0 // ���а� ������.
};

#endif // GAMESTATE_H
// Path: src/enums/GameState.h