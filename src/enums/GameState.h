#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GameState // 한 게임의 상태를 의미한다.
{
    BOTH=1, // 둘 다 둘 수 있다.
    PASS_USER_ONLY=2, // 사용자만 둘 수 있다.
    PASS_COMPUTER_ONLY=3, // 컴퓨터만 둘 수 있다.
    NONE=0 // 승패가 정해짐.
};

#endif // GAMESTATE_H
// Path: src/enums/GameState.h