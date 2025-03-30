#include "Rook.h"
#include "Game.h"

extern Game *game;

Rook::Rook(QString side,QGraphicsItem *parent):ChessPiece(side,parent) {
    setImage();
}

void Rook::setImage() {
    if(side == "WHITE")
        setPixmap(QPixmap(":/res/Res/c_wr.png").scaled(60,60));
    else
        setPixmap(QPixmap(":/res/Res/c_br.png").scaled(60,60));
}

void Rook::moves() {
    // Clear previous locations if any
    location.clear();
    // get the coordinates of current piece selected
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    // Get the side/team of current piece
    QString team = this->getSide();
     //  For Going Upward
     for(int i = row-1,j = col; i >= 0 ; i--) {
         // Check if it some box has our teams piece (Some piece is blocking the path)
       if(game->ChessBoard[i][j]->getChessPieceColor() == team ) break;
       else  {
           location.append(game->ChessBoard[i][j]);
           if(boxSetting(location.last())) break;
        }
    }
    //For Going Downward
    for(int i = row+1,j = col; i <= 7 ; i++) {
      if(game->ChessBoard[i][j]->getChessPieceColor() == team ) break;
      else {
        location.append(game->ChessBoard[i][j]);
        if(boxSetting(location.last())) break;
      }
    }
   //For Going left side
    for(int i = row,j = col-1; j >= 0 ; j--) {
      if(game->ChessBoard[i][j]->getChessPieceColor() == team )  break;
      else{
          location.append(game->ChessBoard[i][j]);
          if(boxSetting(location.last()))  break;
         }
    }
   //For Going Right side
   for(int i = row,j = col+1; j <= 7 ; j++){
     if(game->ChessBoard[i][j]->getChessPieceColor() == team )  break;
      else{
          location.append(game->ChessBoard[i][j]);
          if(boxSetting(location.last()))  break;
         }
     }
}
