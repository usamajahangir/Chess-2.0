#include "Chess_Board.h"
#include "Chess_Box.h"
#include "Game.h"
#include "Queen.h"
#include "Rook.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Bishop.h"

#include <QDebug>

extern Game *game;

Board::Board() {
    setUpBlack();
    setUpWhite();

    loadedwhite.clear();
    loadedblack.clear();
}

Board::~Board(){
    for (int i = white.size(); i > 0 ; --i) delete white[i];
    for (int i = black.size(); i > 0 ; --i) delete black[i];
    for (int i = loadedwhite.size(); i > 0 ; --i) delete loadedwhite[i];
    for (int i = loadedblack.size(); i > 0 ; --i) delete loadedblack[i];
}

void Board::drawBoxes(int x,int y) {
    int SHIFT = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            Chess_Box *box = new Chess_Box();
            game->ChessBoard[i][j] = box;
            game->listG.append(box);
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::lightGray);
            else
                box->setOriginalColor(Qt::darkGray);
            game->addToScene(box);
        }
    }
}

void Board::setUpWhite() {
    white.clear();
    ChessPiece *piece;
    // initialize pieces and save thier pointers to the repective LIST
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("WHITE");
        white.append(piece);
    }
    piece = new Rook("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Queen("WHITE");
    white.append(piece);
    piece = new King("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Rook("WHITE");
    white.append(piece);
}

void Board::setUpBlack() {
    black.clear();
    ChessPiece *piece;
    // initialize pieces and save thier pointers to the repective LIST
    piece = new Rook("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Queen("BLACK");
    black.append(piece);
    piece = new King("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Rook("BLACK");
    black.append(piece);
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("BLACK");
        black.append(piece);
    }
}

void Board::loadwhite(QList<QString> piece_name, QList <QString> side){
    loadedwhite.clear();
    ChessPiece* piece;
    // Initialize pieces that were loaded
    for (int i = 0, n = piece_name.size(); i < n ; ++i){
            if (side[i] == "WHITE"){
               if (piece_name[i] == "King"){
                   piece = new King("WHITE");
                   loadedwhite.append(piece);
               }
               else if (piece_name[i] == "Queen"){
                   piece = new Queen("WHITE");
                   loadedwhite.append(piece);
               }
               else if (piece_name[i] == "Bishop"){
                   piece = new Bishop("WHITE");
                   loadedwhite.append(piece);
               }
               else if (piece_name[i] == "Rook"){
                   piece = new Rook("WHITE");
                   loadedwhite.append(piece);
               }
               else if (piece_name[i] == "Knight"){
                   piece = new Knight("WHITE");
                   loadedwhite.append(piece);
               }
               else if (piece_name[i] == "Pawn"){
                   piece = new Pawn("WHITE");
                   qDebug() << loadedwhite.empty();
                   for (int i =0, n = loadedwhite.size(); i<n ;++i)
                          qDebug() << loadedwhite[i];
                   loadedwhite.append(piece);
               }
               else continue;
            }
            else continue;
        }
}

void Board::loadblack(QList<QString> piece_name, QList <QString> side){
    loadedblack.clear();
    ChessPiece* piece;
    // Initialize pieces that were loaded
    for (int i = 0, n = piece_name.size(); i < n ; ++i){
            if (side[i] == "BLACK"){
               if (piece_name[i] == "King"){
                   piece = new King("BLACK");
                   loadedblack.append(piece);
               }
               else if (piece_name[i] == "Queen"){
                   piece = new Queen("BLACK");
                   loadedblack.append(piece);
               }
               else if (piece_name[i] == "Bishop"){
                   piece = new Bishop("BLACK");
                   loadedblack.append(piece);
               }
               else if (piece_name[i] == "Rook"){
                   piece = new Rook("BLACK");
                   loadedblack.append(piece);
               }
               else if (piece_name[i] == "Knight"){
                   piece = new Knight("BLACK");
                   loadedblack.append(piece);
               }
               else if (piece_name[i] == "Pawn"){
                   piece = new Pawn("BLACK");
                   loadedblack.append(piece);
               }
            }
            else continue;
        }
}

void Board::addChessPiece() {
    // Place the pieces to each box of chess board according to game rules
    int k = 0, h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            Chess_Box *box =game->ChessBoard[i][j];
            game->addToScene(box);
            if(i < 2) {
                box->PlacePiece(black[k]);
                game->alivePiece.append(black[k]);
                game->listG.append(black[k]);
                game->addToScene(black[k++]);         
            }
            if(i > 5) {
                box->PlacePiece(white[h]);
                game->alivePiece.append(white[h]);
                game->listG.append(white[h]);
                game->addToScene(white[h++]);
            }
        }
    }
}

void Board::loadChessPiece(QList<QString> side, QList<QString> piece_name, QList<int> posx, QList<int> posy){
    // Place the pieces to each box of chess board according to game rules
    int h = 0 , k = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++){
            Chess_Box *box =game->ChessBoard[i][j];
            game->addToScene(box);
            for (int alpha = 0, l = posx.size(); alpha < l ; alpha++){
                if (i == posx[alpha] && j == posy[alpha]){
                    if (side[alpha] == "WHITE"){
                        box->PlacePiece(loadedwhite[h]);
                        game->alivePiece.append(loadedwhite[h]);
                        game->listG.append(loadedwhite[h]);
                        game->addToScene(loadedwhite[h++]);
                    }
                    else{
                        box->PlacePiece(loadedblack[k]);
                        game->alivePiece.append(loadedblack[k]);
                        game->listG.append(loadedblack[k]);
                        game->addToScene(loadedblack[k++]);
                    }
                }
            }
        }
    }
}

void Board::reset() {
    int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            Chess_Box *box =game->ChessBoard[i][j];
            // Reset required features for the chess board
            box->setHasChessPiece(false);
            box->setChessPieceColor("NONE");
            box->currentPiece = NULL;
            // Place the pieces again to default positions
            if(i < 2) {
                box->PlacePiece(black[k]);
                black[k]->setIsPlaced(true);
                black[k]->firstMove = true;
                game->alivePiece.append(black[k++]);
            }
            if(i > 5) {
                box->PlacePiece(white[h]);
                white[h]->setIsPlaced(true);
                white[h]->firstMove = true;
                game->alivePiece.append(white[h++]);
            }
        }
    }
}
