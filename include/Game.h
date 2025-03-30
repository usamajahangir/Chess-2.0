#ifndef GAME_H
#define GAME_H

// Libraries useed
#include <QGraphicsView>  // Widegets
#include <QGraphicsScene>
#include <QApplication>
#include <QDesktopWidget>
#include <QString>
#include <QBrush>
#include <QImage>
#include <QKeyEvent>
// Project header Files
#include "Button.h"
#include "Chess_Piece.h"
#include "Chess_Board.h"
#include "Chess_Box.h"

class Board;
class Chess_Box;

class Game : public QGraphicsView{
    Q_OBJECT
public:
    // Constructors
    Game(QWidget *parent = NULL);

    // Methods
    void Show_Menu();
    void drawChessBoard();
    void drawDeadPieceHolder(int x, int y, QColor color);

    void displayDeadWhite();
    void displayDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);
    void keyPressEvent(QKeyEvent *event);
    void Show_PauseScreen();
    void Start_Game(QString type);
    // Adding and removing items from the scene
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    // getter and setters
    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();

    // Public Attributes
    ChessPiece *PieceToMove;
    Chess_Box *ChessBoard[8][8];
    QGraphicsTextItem *check;
    bool king_in_check;
    QList <ChessPiece *> alivePiece;
    QList <QGraphicsItem *> listG;
    QList <QGraphicsItem *> listP;
    QList <QString> side;
    QList <QString> piece_name;
    QList <int> posx;
    QList <int> posy;

    // Game ending
    void gameOver(QString Winner);
    void removeAll();
    void Win_Screen(QString Winner);

public slots:
    void call_menu();
    void New_game();
    void Load_game();
    void Show_About();
    void Save_Game();
    void Resume_game();

private:
    QString User_in;
    QString User_was;
    QGraphicsScene* gameScene;
    QList <ChessPiece *> whiteDead;
    QList <ChessPiece *> blackDead;
    QGraphicsRectItem * deadHolder;
    QString turn;
    Board *chess;
    QGraphicsTextItem * turnDisplay;
};
#endif // GAME_H
