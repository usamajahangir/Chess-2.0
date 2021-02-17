#include "Pawn.h"
#include "Game.h"
#include <typeinfo>
#include "King.h"

extern Game * game;

Pawn::Pawn(QString side, QGraphicsItem *parent):ChessPiece(side,parent) {
    setImage();
    firstMove = true;
}

void Pawn::setImage() {
    if(side == "WHITE")
        setPixmap(QPixmap(":/res/Res/c_wp.png").scaled(60,60));
    else
        setPixmap(QPixmap(":/res/Res/c_bp.png").scaled(60,60));
}

void Pawn::moves() {
    // Remove previous location if any
    location.clear();
    // Get the corrdinate for the current piece
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    // As Pawns of both team play differetly so codes are separate
    // For white Pawn
    if(this->getSide() == "WHITE")  {
        // For capturing black's piece on the left
        if(col > 0 && row > 0 && game->ChessBoard[row-1][col-1]->getChessPieceColor() == "BLACK") {
            location.append(game->ChessBoard[row-1][col-1]);
            boxSetting(location.last());
        }
        // For capturing Black's piece on the right
        if(col < 7 && row > 0 && game->ChessBoard[row-1][col+1]->getChessPieceColor() == "BLACK") {
            location.append(game->ChessBoard[row-1][col+1]);
            boxSetting(location.last());
        }
        // For the First time move
        if(row>0 && (!game->ChessBoard[row-1][col]->getHasChessPiece())) {
            location.append(game->ChessBoard[row-1][col]);
            boxSetting(location.last());
            if(firstMove && row == 6 && !game->ChessBoard[row-2][col]->getHasChessPiece()){
                location.append(game->ChessBoard[row-2][col]);
                boxSetting(location.last());
            }
        }
    }
    // For Black Pawn
    else{
        // For capturing White's piece on the left
        if(col > 0 && row < 7 && game->ChessBoard[row+1][col-1]->getChessPieceColor() == "WHITE") {
            location.append(game->ChessBoard[row+1][col-1]);
          boxSetting(location.last());
        }
        // For capturing White's piece on the right
        if(col < 7 && row <  7 && game->ChessBoard[row+1][col+1]->getChessPieceColor() == "WHITE") {
            location.append(game->ChessBoard[row+1][col+1]);
             boxSetting(location.last());
        }
        // For the first time move
        if(row<7 && (!game->ChessBoard[row+1][col]->getHasChessPiece())) {
            location.append(game->ChessBoard[row+1][col]);
            boxSetting(location.last());
            if(firstMove && row == 1  && !game->ChessBoard[row+2][col]->getHasChessPiece()){
                location.append(game->ChessBoard[row+2][col]);
                boxSetting(location.last());
            }
        }
    }
}


