#ifndef BOX_H
#define BOX_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include "Chess_Piece.h"
#include <QBrush>

class ChessPiece;

class Chess_Box : public QGraphicsRectItem{
public:
    //Constructor
    Chess_Box(QGraphicsItem *parent= NULL);
    // Distructor
    ~Chess_Box();

    //public methods

    // For mouse event on any box
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void PlacePiece(ChessPiece *piece);

    // For functioning related to box color
    void SetColor(QColor color);
    void resetOriginalColor();
    void setOriginalColor(QColor value);
    QString getChessPieceColor() ;
    void setChessPieceColor(QString value);

    // State check Methods
    bool getHasChessPiece();
    void setHasChessPiece(bool value,ChessPiece *piece = 0);

    // For Checking if the King is in check state
    void TestCheck();

    // Location Attributes
    int rowLoc;
    int colLoc;

    ChessPiece * currentPiece;
private:
    QBrush brush;
    QColor originalColor;
    bool hasPiece;
    QString PieceColor;
};

#endif // BOX_H
