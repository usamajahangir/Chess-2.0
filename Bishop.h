#ifndef BISHOP_H
#define BISHOP_H

#include "Chess_Piece.h"
#include "Chess_Box.h"

class Bishop : public ChessPiece{
public:
    // Constructor
    Bishop(QString side,QGraphicsItem *parent = 0);
    // Methods
    void setImage();
    void moves();
};

#endif // BISHOP_H
