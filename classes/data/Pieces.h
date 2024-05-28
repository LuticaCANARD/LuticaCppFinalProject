#ifndef PIECES_H
#define PIECES_H

class Pieces
{
    // Ware를 승계하여, 
    // Piece는 보드위에 나타난 말이 컴퓨터인지 사용자인지를 나타내는 클래스이다.

private :
    // 이 기물이 컴퓨터라면 True
    bool computer; 
public :
/**
 * @brief Construct a new Pieces object
 * 
 * @param _isComputer 
 */
    Pieces(bool _isComputer);
    bool getComputer();
};

#endif // PIECES_H
// Path: classes/data/Pieces.cpp