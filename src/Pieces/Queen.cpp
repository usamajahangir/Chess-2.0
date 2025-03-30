#include "Queen.h"
#include "Game.h"

extern Game *game;

Queen::Queen(QString side,QGraphicsItem *parent):ChessPiece(side,parent) {
    setImage();
}

void Queen::setImage() {
    if(side == "WHITE")
        setPixmap(QPixmap(":/res/Res/c_wq.png").scaled(60,60));
    else
        setPixmap(QPixmap(":/res/Res/c_bq.png").scaled(60,60));
}

void Queen::moves() {
    // Clear previous locations if any
    location.clear();
    // get corrdinate for the current piece selected
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    // get the current piece side/team
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
      //For upper Left
       for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
         if(game->ChessBoard[i][j]->getChessPieceColor() == team ) break;
         else{
             location.append(game->ChessBoard[i][j]);
             if(boxSetting(location.last()) ) break;
         }
      }
     //For upper right
     for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
         if(game->ChessBoard[i][j]->getChessPieceColor() == team ) break;
         else {
              location.append(game->ChessBoard[i][j]);
              if(boxSetting(location.last())) break;
          }
       }
      //For downward right
     for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
           if(game->ChessBoard[i][j]->getChessPieceColor() == team ) break;
           else {
               location.append(game->ChessBoard[i][j]);
               if(boxSetting(location.last())) break;
           }
        }
    //For downward left
     for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
         if(game->ChessBoard[i][j]->getChessPieceColor() == team ) break;
         else{
                location.append(game->ChessBoard[i][j]);
                if(boxSetting(location.last()))break;
            }
         }
}
