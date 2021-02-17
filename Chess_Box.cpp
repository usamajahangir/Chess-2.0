#include "Chess_Box.h"
#include "Game.h"
#include "King.h"

extern Game *game;

Chess_Box::Chess_Box(QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    // making box using rectangle to represent a chess box
    this->setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");
    currentPiece = NULL;
}

Chess_Box::~Chess_Box(){
    delete this;
}

void Chess_Box::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // Deselecting Chess Piece if already selected using another function
     if((currentPiece == game->PieceToMove)&& currentPiece){
        currentPiece->mousePressEvent(event);
        return;
    }
    // If the piece is selected and new position (box) is given
    if(game->PieceToMove){
       // If the this box is obtained by the same sided piece
        if (this->getChessPieceColor() == game->PieceToMove->getSide()) return;
       // Removing the captured piece
       QList <Chess_Box*> movLoc = game->PieceToMove->moveLocation();
       //TO make sure the selected box is in move zone
       int check = 0;
       for(size_t i = 0, n = movLoc.size(); i < n;i++) {
           if(movLoc[i] == this)   check++;
       }
       // if not present return
       if(check == 0) return;
       //change the color back to normal
        game->PieceToMove->decolor();
        //make the first move false applicable for pawn only
        game->PieceToMove->firstMove = false;
        //if to capture the enemy present inn the movable region
       if(this->getHasChessPiece()){
           this->currentPiece->setIsPlaced(false);
           this->currentPiece->setCurrentBox(NULL);
           game->placeInDeadPlace(this->currentPiece);
       }
       //Updating board states
       game->PieceToMove->getCurrentBox()->setHasChessPiece(false);
       game->PieceToMove->getCurrentBox()->currentPiece = NULL;
       game->PieceToMove->getCurrentBox()->resetOriginalColor();
       PlacePiece(game->PieceToMove);
       game->PieceToMove = NULL;
       //changing turn
       game->changeTurn();
       // Check if the king is in check state
       TestCheck();
   }
   //Selecting couterpart of the chessPiece
   else if(this->getHasChessPiece())
       this->currentPiece->mousePressEvent(event);
}

void Chess_Box::SetColor(QColor color){
    brush.setColor(color);
    setBrush(color);
}

void Chess_Box::PlacePiece(ChessPiece *piece){
    piece->setPos (x() + 50 - piece->pixmap().width()/2, y() + 50 - piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;
}

void Chess_Box::resetOriginalColor(){
    SetColor(originalColor);
}

void Chess_Box::setOriginalColor(QColor value){
    originalColor = value;
    SetColor(originalColor);
}

bool Chess_Box::getHasChessPiece() {
    // return the attribute containing the required information
    return hasPiece;
}

void Chess_Box::setHasChessPiece(bool value, ChessPiece *piece) {
    //  Set the attribute equal to the passed value
      hasPiece = value;
    // set the chess piece color according to the side
    if(value)
        setChessPieceColor(piece->getSide());
    else
        setChessPieceColor("NONE");
}

void Chess_Box::TestCheck() {
    int c = 0;
    QList <ChessPiece *> pList = game->alivePiece;
    for(size_t i = 0,n=pList.size(); i < n; i++ ) {
        King * p = dynamic_cast<King *> (pList[i]);
        if(p) continue;
        pList[i]->moves();
        pList[i]->decolor();
        QList <Chess_Box *> bList = pList[i]->moveLocation();
        for(size_t j = 0,n = bList.size(); j < n; j ++) {
            King * p = dynamic_cast<King *> (bList[j]->currentPiece);
            if(p) {
                if(p->getSide() == pList[i]->getSide()) continue;
                bList[j]->SetColor(Qt::blue);
                pList[i]->getCurrentBox()->SetColor(Qt::darkRed);
                if(!game->check->isVisible())
                    game->check->setVisible(true);
                c++;
            }
        }
    }
    if(!c){
        game->check->setVisible(false);
        for(size_t i = 0,n=pList.size(); i < n; i++ )
            pList[i]->getCurrentBox()->resetOriginalColor();
    }
}

QString Chess_Box::getChessPieceColor() {
    return PieceColor;
}

void Chess_Box::setChessPieceColor(QString value) {
     PieceColor = value;
}
