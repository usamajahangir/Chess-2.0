#include "King.h"
#include "Game.h"
#include "Pawn.h"

extern Game *game;

King::King(QString side,QGraphicsItem *parent):ChessPiece(side,parent) {
    setImage();
}

void King::setImage() {
    if(side == "WHITE")
        setPixmap(QPixmap(":/res/Res/c_wk.png").scaled(60,60));
    else
        setPixmap(QPixmap(":/res/Res/c_bk.png").scaled(60,60));
}

void King::moves() {
    // Remove previous locations if any
    location.clear();
    // Get the corrdinate for the current piece
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    // Get the side/team of current piece
    QString team = this->getSide();


    //////////////////////  NOTE  /////////////////////////////////
    //  As There are only 8 adjacent boxes where the king can go //
    // so we are hardcoding this as well                         //
    // Along with giving it the color                            //
    ///////////////////////////////////////////////////////////////


    // For UP
    if(row>0 && !(game->ChessBoard[row-1][col]->getChessPieceColor() == team)) {
        location.append(game->ChessBoard[row-1][col]);
        game->ChessBoard[row-1][col]->SetColor(Qt::darkRed);
        if(location.last()->getHasChessPiece()){
            location.last()->SetColor(Qt::red);
        }
    }
    // For Down
    if(row<7 && !(game->ChessBoard[row+1][col]->getChessPieceColor() == team)) {
        location.append(game->ChessBoard[row+1][col]);
        game->ChessBoard[row+1][col]->SetColor(Qt::darkRed);
        if(location.last()->getHasChessPiece()){
            location.last()->SetColor(Qt::red);
        }
    }
    // For Left
    if(col>0 && !(game->ChessBoard[row][col-1]->getChessPieceColor() == team)) {
        location.append(game->ChessBoard[row][col-1]);
        game->ChessBoard[row][col-1]->SetColor(Qt::darkRed);
        if(location.last()->getHasChessPiece()){
            location.last()->SetColor(Qt::red);
        }
    }
    // For Right
    if(col<7 && !(game->ChessBoard[row][col+1]->getChessPieceColor() == team)) {
        location.append(game->ChessBoard[row][col+1]);
        game->ChessBoard[row][col+1]->SetColor(Qt::darkRed);
        if(location.last()->getHasChessPiece()){
            location.last()->SetColor(Qt::red);
        }
    }
    // For UpLeft
    if(col > 0 && row > 0 && !(game->ChessBoard[row-1][col-1]->getChessPieceColor() == team)) {
        location.append(game->ChessBoard[row-1][col-1]);
        game->ChessBoard[row-1][col-1]->SetColor(Qt::darkRed);
        if(location.last()->getHasChessPiece()){
            location.last()->SetColor(Qt::red);
        }
    }
    // For UpRight
    if(col < 7 && row > 0 && !(game->ChessBoard[row-1][col+1]->getChessPieceColor() == team)) {
        location.append(game->ChessBoard[row-1][col+1]);
        game->ChessBoard[row-1][col+1]->SetColor(Qt::darkRed);
        if(location.last()->getHasChessPiece()){
            location.last()->SetColor(Qt::red);
        }
    }
    // For DownLeft
    if(col > 0 && row < 7  && !(game->ChessBoard[row+1][col-1]->getChessPieceColor() == team)) {
        location.append(game->ChessBoard[row+1][col-1]);
        game->ChessBoard[row+1][col-1]->SetColor(Qt::darkRed);
        if(location.last()->getHasChessPiece()){
            location.last()->SetColor(Qt::red);
        }
    }
    // For Down Right
    if(col < 7 && row < 7 && !(game->ChessBoard[row+1][col+1]->getChessPieceColor() == team)) {
        location.append(game->ChessBoard[row+1][col+1]);
        game->ChessBoard[row+1][col+1]->SetColor(Qt::darkRed);
        if(location.last()->getHasChessPiece()){
            location.last()->SetColor(Qt::red);
        }
    }
    findUnSafeLocation();
}

void King::findUnSafeLocation() {
    // Get all the pices present on the chess board alive
    QList <ChessPiece *> pList = game->alivePiece;
    for(size_t i = 0,n = pList.size(); i < n; i++) {
        if(pList[i]->getSide() != this->getSide()){
            QList <Chess_Box *> bList = pList[i]->moveLocation();
            for(size_t j = 0, n = bList.size(); j < n; j++) {
                Pawn *c = dynamic_cast<Pawn *> (pList[i]) ;
                if(c) continue;
                for(size_t k = 0, n = location.size(); k < n; k++) {
                   if(bList[j] == location [k]) {
                       location[k]->SetColor(Qt::blue);
                   }
                }
            }
        }
    }
}
