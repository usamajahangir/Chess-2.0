#include "Chess_Piece.h"
#include "King.h"

extern Game *game;

ChessPiece::ChessPiece(QString side, QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    this->side = side;
    isPlaced = true;
    // Flag fro Empassent move
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // If same piece is selected which was already selected deselect
    if(this == game->PieceToMove){
        game->PieceToMove->getCurrentBox()->resetOriginalColor();
        game->PieceToMove->decolor();
        game->PieceToMove = NULL;
        return;
    }
    //if it is already captured or not the respective color's turn
    if((!getIsPlaced() )|| ( (game->getTurn() != this->getSide())&& (!game->PieceToMove)) )
        return;
    //selecting
    if(!game->PieceToMove){
        game->PieceToMove = this;
        game->PieceToMove->getCurrentBox()->SetColor(Qt::red);
        game->PieceToMove->moves();
    }
    // otherwise capture that chess box
    else if(this->getSide() != game->PieceToMove->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }
}

void ChessPiece::setCurrentBox(Chess_Box *box){
    currentBox = box;
}

Chess_Box *ChessPiece::getCurrentBox(){
    return currentBox;
}

QString ChessPiece::getSide(){
    return side;
}

void ChessPiece::setSide( QString value){
    side = value;
}

bool ChessPiece::getIsPlaced(){
    return isPlaced;
}

void ChessPiece::setIsPlaced(bool value){
    isPlaced = value;
}

QList<Chess_Box *> ChessPiece::moveLocation(){
    return location;
}

void ChessPiece::decolor() {
    for(size_t i = 0, n = location.size(); i < n;i++)
         location[i]->resetOriginalColor();
}

bool ChessPiece::boxSetting(Chess_Box *box) {
    // Set the kings box to blue if  it is in check condition
    if(box->getHasChessPiece()) {
        King *q = dynamic_cast<King*>(location.last()->currentPiece);
        if(q){
            box->SetColor(Qt::blue);
        }
        else
            box->SetColor(Qt::red);
        return true;
    }
    else
        location.last()->SetColor(Qt::darkRed);
    return false;
}
