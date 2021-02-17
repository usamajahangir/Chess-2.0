#ifndef QUEEN_H
#define QUEEN_H

#include "Chess_Piece.h"
#include "Bishop.h"

class Queen :  public ChessPiece {
public:
    // Constructor
    Queen(QString side,QGraphicsItem *parent = 0);
    // Methods
    void setImage();
    void moves();
};
#endif // QUEEN_H
