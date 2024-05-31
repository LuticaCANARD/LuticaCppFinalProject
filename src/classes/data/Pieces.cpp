/**
 * @brief �⹰�� �����ϴ� class
 * (Ware�� �ʹ� �дٴ� ������ ����, �̸��� �����ϴ� refactor�� ������.)
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
