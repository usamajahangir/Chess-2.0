#ifndef PAWN_H
#define PAWN_H

#include "Chess_Piece.h"

class Pawn : public ChessPiece {
public:
    // Contructor
    Pawn(QString side,QGraphicsItem *parent = 0);
    // Methods
    void setImage();
    void moves();
};
#endif // PAWN_H
