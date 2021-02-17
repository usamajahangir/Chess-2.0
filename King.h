#ifndef KING_H
#define KING_H

#include "Chess_Piece.h"

class King : public ChessPiece{
public:
    // Constructor
    King(QString side,QGraphicsItem *parent = 0);
    // Methods
    void setImage();
    void moves();
    void findUnSafeLocation();
};
#endif // KING_H
