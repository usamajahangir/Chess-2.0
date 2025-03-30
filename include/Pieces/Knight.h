#ifndef KNIGHT_H
#define KNIGHT_H

#include "Chess_Piece.h"

class Knight : public ChessPiece {
public:
    // Constructor
    Knight(QString side,QGraphicsItem *parent = 0);
    // Methods
    void setImage();
    void moves();
};
#endif // KNIGHT_H
