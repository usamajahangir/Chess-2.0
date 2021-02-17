#include "Bishop.h"
#include "Game.h"

extern Game *game;

Bishop::Bishop(QString side,QGraphicsItem *parent) : ChessPiece(side,parent){
    setImage();
}

void Bishop::setImage(){
    if(side == "WHITE")
        setPixmap(QPixmap(":/res/Res/c_wb.png").scaled(60,60));
    else
        setPixmap(QPixmap(":/res/Res/c_bb.png").scaled(60,60));
}

void Bishop::moves(){
    // remove previous locations if any
    location.clear();
    // get the cordinates for teh current piece
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    // Get the side/team of current piece
    QString team = this->getSide();

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
