///////////////   Chess 2.0 Project   //////////////

//////////////////  Developers  ////////////////////
//                                                //
//  Usama Jahangir   - Lead Developer             //
//  Wajid Ali        - Co-Developer               //
//                                                //
////////////////////////////////////////////////////


// The project is based of the my own Chess project for FOP in 2nd Semester
// This project include just the algorithm from the Chess 1.0 (My old Chess)

#include <QApplication>
#include <QIcon>
#include <QCursor>
#include "Game.h"

Game* game;

// This is the main function of Chess which creates a Main Menu instance and than shows it.
int main(int argc, char *argv[]) {
    QApplication Chess(argc, argv);

    // Set Icon and name for the application
    Chess.setWindowIcon(QIcon(":/res/Res/Chess_Icon.png"));
    Chess.setApplicationName("Chess 2.0");

    // Show the Main Menu
    game = new Game();
    game->setCursor(Qt::CrossCursor);
    game->show();
    game->Show_Menu();

    return Chess.exec();
}
