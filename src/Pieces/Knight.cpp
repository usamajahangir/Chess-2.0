#include "Knight.h"
#include "Game.h"

extern Game *game;

Knight::Knight(QString side,QGraphicsItem *parent):ChessPiece(side,parent) {
    setImage();
}

void Knight::setImage() {
    if(side == "WHITE")
        setPixmap(QPixmap(":/res/Res/c_wn.png").scaled(60,60));
    else
        setPixmap(QPixmap(":/res/Res/c_bn.png").scaled(60,60));
}

void Knight::moves() {
    // Remove previous location if any
    location.clear();
    // get the corrdinate for the current piece
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    int i ,j;
    // Get the side/team of current piece
    QString team  = this->getSide();

   //////////////////////  NOTE  /////////////////////////////////
   //  As there are only 8 place any knight can go on and those //
   //  are not sequance wise so we are hardcoding for each      //
   //  position                                                 //
   //  Also coloring at the same time                           //
   ///////////////////////////////////////////////////////////////

    //  For going  (UP-UP-then-Left)
    i = row - 2;
    j = col - 1;
    if(i >=0 && j>=0 && (game->ChessBoard[i][j]->getChessPieceColor() != team) ) {
        location.append(game->ChessBoard[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->SetColor(Qt::red);
        else
            location.last()->SetColor(Qt::darkRed);
    }
    //  For going  (UP-UP-then-Right)
    i = row - 2;
    j = col + 1;
    if(i >=0 && j<=7 && (game->ChessBoard[i][j]->getChessPieceColor() != team) ) {
        location.append(game->ChessBoard[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->SetColor(Qt::red);
        else
            location.last()->SetColor(Qt::darkRed);
    }
    //  For going  (Down-Down-then-Left)
    i = row + 2;
    j = col - 1;
    if(i <= 7 && j>=0 && (game->ChessBoard[i][j]->getChessPieceColor() != team) ) {
        location.append(game->ChessBoard[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->SetColor(Qt::red);
        else
            location.last()->SetColor(Qt::darkRed);
    }
    //  For going  (Down-Down-then-Rigt)
    i = row + 2;
    j = col + 1;
    if(i <=7 && j<=7 && (game->ChessBoard[i][j]->getChessPieceColor() != team) ) {
        location.append(game->ChessBoard[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->SetColor(Qt::red);
        else
            location.last()->SetColor(Qt::darkRed);
    }
    //  For going  (Left-Left-then-UP)
    i = row - 1;
    j = col - 2;
    if(i >=0 && j>=0 && (game->ChessBoard[i][j]->getChessPieceColor() != team) ) {
        location.append(game->ChessBoard[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->SetColor(Qt::red);
        else
            location.last()->SetColor(Qt::darkRed);
    }
    //  For going  (Left-Left-then-Down)
    i = row + 1;
    j = col - 2;
    if(i <=7 && j>=0 && (game->ChessBoard[i][j]->getChessPieceColor() != team) ) {
        location.append(game->ChessBoard[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->SetColor(Qt::red);
        else
            location.last()->SetColor(Qt::darkRed);
    }
    //  For going  (Right-Right-then-Up)
    i = row - 1;
    j = col + 2;
    if(i >=0 && j<=7 && (game->ChessBoard[i][j]->getChessPieceColor() != team) ) {
        location.append(game->ChessBoard[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->SetColor(Qt::red);
        else
            location.last()->SetColor(Qt::darkRed);
    }
    //  For going  (Right-Right-then-Down)
    i = row + 1;
    j = col +  2;
    if(i <=7 && j<=7 && (game->ChessBoard[i][j]->getChessPieceColor() != team) ) {
        location.append(game->ChessBoard[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->SetColor(Qt::red);
        else
            location.last()->SetColor(Qt::darkRed);
    }
}
