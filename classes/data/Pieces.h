#ifndef PIECES_H
#define PIECES_H

class Pieces
{
    // Ware�� �°��Ͽ�, 
    // Piece�� �������� ��Ÿ�� ���� ��ǻ������ ����������� ��Ÿ���� Ŭ�����̴�.

private :
    // �� �⹰�� ��ǻ�Ͷ�� True
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