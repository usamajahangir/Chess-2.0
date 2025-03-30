#ifndef ROOK_H
#define ROOK_H

#include "Chess_Piece.h"

class Rook : public ChessPiece {
public:
    // Constructor
    Rook(QString side, QGraphicsItem *parent = 0);
    // Methods
    void setImage();
    void moves();
};
#endif // ROOK_H
