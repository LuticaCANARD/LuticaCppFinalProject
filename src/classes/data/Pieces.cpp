/**
 * @brief 기물을 정의하는 class
 * (Ware가 너무 넓다는 문제에 따라서, 이름을 변경하는 refactor를 집행함.)
 */

#include "Pieces.h"

Pieces::Pieces(bool _isComputer){
    this->computer = _isComputer;
}
Pieces::Pieces(const Pieces& _piece){
    this->computer = _piece.computer;
}

bool Pieces::getComputer(){
    return this->computer;
}

void Pieces::reverse(){
    this->computer = !this->computer;
}
// Path: classes/data/Pieces.h
