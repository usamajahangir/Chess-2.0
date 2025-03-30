#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "Chess_Box.h"
#include "Game.h"

//  Chess Piece is Abstract class from which All diffferent pieces classes are derived
class ChessPiece : public QGraphicsPixmapItem{
public:
    // Constructors
    ChessPiece(QString side = "",QGraphicsItem *parent = 0);

    // public methods
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // Getters and setter
    void setCurrentBox(Chess_Box *box);
    Chess_Box *getCurrentBox() ;
    QString getSide() ;
    void setSide( QString value);
    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <Chess_Box *> moveLocation();
    void decolor();
    bool boxSetting(Chess_Box *box);

    // Empassent move attribute
    bool firstMove;

    // Pure Virtual Methods
    virtual void moves() = 0;
    virtual void setImage() = 0;
protected:
    Chess_Box *currentBox;
    QString side;
    bool isPlaced;
    QList <Chess_Box *> location;
};
#endif // CHESSPIECE_H
