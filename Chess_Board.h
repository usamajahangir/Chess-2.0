#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsRectItem>
#include "Chess_Piece.h"
#include <QList>

class ChessPiece;

class Board {
public:
    // Constructor
    Board();
    ~Board();

    // Public methods

    // To draw boxes
    void drawBoxes(int x, int y);

    // To initialize pieces
    void setUpWhite();
    void setUpBlack();

    void loadwhite(QList <QString> piece_name, QList <QString> side);
    void loadblack(QList <QString> piece_name, QList <QString> side);

    // To add the initilized pieces to the board (each box as per requirment)
    void addChessPiece();
    void loadChessPiece(QList <QString> side, QList <QString> piece_name,  QList <int> posx, QList <int> posy);

    // To reset to default status
    void reset();
    // For new pieces
    QList <ChessPiece *> white;
    QList <ChessPiece *> black;
    // for loaded pieces
    QList <ChessPiece *> loadedwhite;
    QList <ChessPiece *> loadedblack;

private:
    // List to keep the pointers for the initilized pieces

};

#endif // CHESSBOARD_H
