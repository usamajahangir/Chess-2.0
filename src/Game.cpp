#include "Game.h"
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QGraphicsItem>
#include "Image.h"
// Pieces classes
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"

extern Game* game;
static bool on;

Game::Game(QWidget *parent):QGraphicsView(parent){
    on = true;
    // Set up the Display (Scene)
    gameScene = new QGraphicsScene();
    QRect rec = QApplication::desktop()->screenGeometry();
    auto height = rec.height();
    auto width = rec.width();
    gameScene->setSceneRect(0,0,width, height);
    // Making Full Screen
    this->showFullScreen();

    // Setting the view
    setFixedSize(width,height);
    // Set Background image
    QImage image = QImage(":/res/Res/Menu_background.jpg");
    QImage resized = image.scaled(width,height);
    gameScene->setBackgroundBrush(QBrush(QImage(resized)));

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Set the game scene
    setScene(gameScene);

    PieceToMove= NULL;

    //display turn
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turn : WHITE");
    turnDisplay->setOpacity(1);
    listG.append(turnDisplay);

    //display Check
    check = new QGraphicsTextItem();
    check->setPos(width/2-100,860);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::darkRed);
    check->setFont(QFont("",25));
    check->setPlainText("!!!!   CHECK  !!!!");
    check->setVisible(false);
    listG.append(check);
    setTurn("WHITE");

    //  set user current status
    User_in = "";
    User_was = "";
}

void Game::Show_Menu(){
    User_in = "Menu";
    User_was = "Menu";
    //  Remove any old item in the scene
    for(size_t i =0, n = listP.size(); i < n; i++)
            removeFromScene(listP[i]);
    for(size_t i =0, n = listG.size(); i < n; i++)
        removeFromScene(listG[i]);

    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Chess 2.0");
    QFont titleFont("Bradley Hand ITC" , 120);
    titleText->setDefaultTextColor(Qt::white);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 80;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);

    //create new game Button
    Button * playButton = new Button("New Game");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 250;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(New_game()));
    addToScene(playButton);
    listG.append(playButton);

    //create Load game Button
    Button * loadButton = new Button("Load Game");
    pxPos = width()/2 - loadButton->boundingRect().width()/2;
    pyPos = 320;
    loadButton->setPos(pxPos,pyPos);
    connect(loadButton,SIGNAL(clicked()) , this , SLOT(Load_game()));
    addToScene(loadButton);
    listG.append(loadButton);

    //create about Button
    Button * AboutButton = new Button("About");
    pxPos = width()/2 - AboutButton->boundingRect().width()/2;
    pyPos = 390;
    AboutButton->setPos(pxPos,pyPos);
    connect(AboutButton,SIGNAL(clicked()) , this , SLOT(Show_About()));
    addToScene(AboutButton);
    listG.append(AboutButton);

    //Create Quit Button
    Button * quitButton = new Button("Quit");
    int qxPos = width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 500;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    //drawChessBoard();
    listG.append(quitButton);
}

void Game::Show_About(){
    User_in = "About";
    //  Remove any old items in the scene
    for(size_t i =0, n = listP.size(); i < n; i++)
            removeFromScene(listP[i]);
    for(size_t i =0, n = listG.size(); i < n; i++)
        removeFromScene(listG[i]);
    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("About !");
    QFont titleFont("Bradley Hand ITC" , 100);
    titleText->setDefaultTextColor(Qt::white);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 80;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);

    // Set the about text
    QGraphicsTextItem *aboutText = new QGraphicsTextItem();
    QFont aboutTextfont("times" , 16);
    aboutText->setDefaultTextColor(Qt::white);
    aboutText->setFont( aboutTextfont);
    aboutText->setPlainText("Developers : \n"
                            "    -->  Usama Jahangir\n"
                            "    -->  Wajid Ali     \n"
                            "\nGame Features:\n"
                            "  1) Complete Chess game\n"
                            "  2) Game saving and loading features\n"
                            "\nProgramming Concept used: \n"
                            "  - Mulitple-Inheritance\n"
                            "  - Inheritance\n"
                            "  - Polymorphism\n"
                            "  - Data Abstraction                                                                 Release Date: 17-02-2021\n"
                            "  - Encapsulation\n ");
    xPos = width()/2 - ((titleText->boundingRect().width()/2)+200);
    yPos = 230;
    aboutText->setPos(xPos,yPos);
    addToScene(aboutText);
    listG.append(aboutText);

    //create return to menu Button
    Button * returnButton = new Button("Go back");
    int pxPos = width() - ((returnButton->boundingRect().width()/2)+200);
    int pyPos = height()-150;
    returnButton->setPos(pxPos,pyPos);
    connect(returnButton,SIGNAL(clicked()) , this , SLOT(call_menu()));
    addToScene(returnButton);
    listG.append(returnButton);
}

void Game::Save_Game(){
    // Call save game method from pieces class
    QString piece_name;
    QString filename="save.png";
    QFile file( filename );
    if ( file.open(QIODevice::WriteOnly) ){
        QTextStream stream( &file );
        stream << game->getTurn() << endl;
        for (int i = 0, n = game->alivePiece.size(); i < n ; ++i){
            QString side = game->alivePiece[i]->getSide();
            stream << side  << endl;
        }
        stream << "GET THE COUNT" << endl;
        for (int i = 0, n = game->alivePiece.size(); i < n ; ++i){
            // Doing dynamic casting to check that alive piece pointer is of which class
            if (King *c = dynamic_cast<King *> (alivePiece[i])) piece_name = "King";
            if (Queen *c = dynamic_cast<Queen *> (alivePiece[i])) piece_name = "Queen";
            if (Knight *c = dynamic_cast<Knight *> (alivePiece[i])) piece_name = "Knight";
            if (Bishop *c = dynamic_cast<Bishop *> (alivePiece[i])) piece_name = "Bishop";
            if (Rook *c = dynamic_cast<Rook *> (alivePiece[i])) piece_name = "Rook";
            if (Pawn *c = dynamic_cast<Pawn *> (alivePiece[i])) piece_name = "Pawn";
            stream << piece_name << endl;
        }
        for (int i = 0, n = game->alivePiece.size(); i < n ; ++i){
            QString locx = QString::number(game->alivePiece[i]->getCurrentBox()->rowLoc);
            stream << locx << endl;
        }
        for (int i = 0, n = game->alivePiece.size(); i < n ; ++i){
            QString locy = QString::number(game->alivePiece[i]->getCurrentBox()->colLoc);
            stream << locy << endl;
        }
    }
    file.flush();
    file.close();
    Show_PauseScreen();
}

void Game::Resume_game(){
    Start_Game("");
}

void Game::drawChessBoard() {
    // Create new chess board
    chess = new Board();
    drawDeadPieceHolder(0,0,Qt::lightGray);
    drawDeadPieceHolder(width()-300,0,Qt::lightGray);
    chess->drawBoxes(width()/2-400,50);
}

void Game::drawDeadPieceHolder(int x, int y,QColor color) {
    deadHolder = new QGraphicsRectItem(x,y,300,height());
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    deadHolder->setBrush(brush);
    addToScene(deadHolder);
    listG.append(deadHolder);
}

void Game::displayDeadWhite() {
    // variable to shift each piece with respect to the first one
    int SHIFT = 50;
    int j = 0, k = 0;
    for(size_t i = 0,n = whiteDead.size(); i<n; i++) {
            if(j == 4){
                k++;
                j = 0;
            }
            // Add the piece at that pos
            whiteDead[i]->setPos(40+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::displayDeadBlack() {
    int SHIFT = 50;
    int j = 0, k = 0;
    for(size_t i = 0,n = blackDead.size(); i<n; i++) {
        if(j == 4){
            k++;
            j = 0;
        }
        // Add the daed piece to that position
        blackDead[i]->setPos((width()-260)+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::keyPressEvent(QKeyEvent *event){
    // When the user presses the escape key
    if (event->key() == Qt::Key_Escape && (User_in == "About" || User_in == "Settings" || User_in == "Load") && User_was == "Menu"){
        // Remove all the items from the current view
       for(size_t i =0, n = listG.size(); i < n; i++)
          removeFromScene(listG[i]);
       // Goto Main Menu
       game->Show_Menu();
    }
    else if (event->key() == Qt::Key_Escape && User_in == "Game" && User_was != "Win"){
        // Goto Pause Screen
        game->Show_PauseScreen();
    }
    else if (event->key() == Qt::Key_Escape && User_in == "Pause" && User_was == "Game"){
        game->Start_Game("");
    }
}

void Game::Show_PauseScreen() {
    User_in = "Pause";
    User_was  = "Game";
    // Decrease the back ground opacity
    for(size_t i =0, n = listG.size(); i < n; i++)
        listG[i]->setOpacity(0.2);

    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Game Paused");
    QFont titleFont("Bradley Hand ITC" , 50);
    titleText->setDefaultTextColor(Qt::white);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listP.append(titleText);

    //create Resume Button
    Button * resume = new Button("Resume");
    int pxPos = width()/2 - resume->boundingRect().width()/2;
    int pyPos = 250;
    resume->setPos(pxPos,pyPos);
    connect(resume,SIGNAL(clicked()) , this , SLOT(Resume_game()));
    addToScene(resume);
    listP.append(resume);

    //create Save Button
    Button * Save = new Button("Save");
    pxPos = width()/2 - Save->boundingRect().width()/2;
    pyPos = 320;
    Save->setPos(pxPos,pyPos);
    connect(Save,SIGNAL(clicked()) , this , SLOT(Save_Game()));
    addToScene(Save);
    listP.append(Save);

    //create return to menu Button
    Button * returnButton = new Button("Main Menu");
    pxPos = width()/2 - returnButton->boundingRect().width()/2;
    pyPos = 450;
    returnButton->setPos(pxPos,pyPos);
    connect(returnButton,SIGNAL(clicked()) , this , SLOT(call_menu()));
    addToScene(returnButton);
    listP.append(returnButton);
}

void Game::placeInDeadPlace(ChessPiece *piece)
{
    if(piece->getSide() == "WHITE") {
        whiteDead.append(piece);
        // If the king is dead (NOT POSSIBLE) TODO: Remove this later
        King *g = dynamic_cast <King *>(piece);
        if(g){
            gameOver("BLACK");
        }
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
        // If the king is dead (NOT POSSIBLE) TODO: Remove this later
        King *g = dynamic_cast <King *>(piece);
        if(g){
            gameOver("WHITE");
        }
        displayDeadBlack();
    }
    alivePiece.removeAll(piece);
}

void Game::addToScene(QGraphicsItem *item){
    gameScene->addItem(item);
}

void Game::removeFromScene(QGraphicsItem *item){
    gameScene->removeItem(item);
}

QString Game::getTurn(){
    return turn;
}

void Game::setTurn(QString value){
    turn = value;
}

void Game::changeTurn(){
    if(getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
    turnDisplay->setPlainText(getTurn() + "'s Turn");
}

void Game::call_menu(){
    removeAll();
    game->Show_Menu();
}

void Game::New_game(){
    turnDisplay->setPlainText("Turn : WHITE");
    Start_Game("New");
}

void Game::Load_game(){
    Start_Game("Load");
}

void Game::Start_Game(QString type){
    alivePiece.clear();
    User_in = "Game";
    User_was = "Game";
    if (type != ""){
    for(size_t i =0, n = listP.size(); i < n; i++)
                removeFromScene(listP[i]);
    for(size_t i =0, n = listG.size(); i < n; i++)
        removeFromScene(listG[i]);

    drawChessBoard();
    turnDisplay->setOpacity(1);
    addToScene(turnDisplay);

    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(70,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::white);
    whitePiece->setFont(QFont("",14));
    whitePiece->setPlainText("WHITE PIECE");
    addToScene(whitePiece);
    listG.append(whitePiece);

    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();
    blackPiece->setPos(width()-200,10);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::white);
    blackPiece->setFont(QFont("",14));
    blackPiece->setPlainText("BLACK PIECE");
    addToScene(blackPiece);
    addToScene(check);
    listG.append(blackPiece);
    }
    if (type == "New"){
        setTurn("WHITE");
        chess->white.clear();
        chess->black.clear();
        chess->setUpBlack();
        chess->setUpWhite();
      chess->addChessPiece();
    }
    else if (type == "Load"){
        side.clear();
        piece_name.clear();
        posx.clear();
        posy.clear();
        int count = 0;
        QString data;
        QString filename="save.png";
        QFile file( filename );
        if ( file.open(QIODevice::ReadOnly) ){
            QTextStream stream( &file );
            while (!file.atEnd()) {
                QByteArray line = file.readLine();
                for (int i =0, n = line.size(); i<n-1 ;i++){
                    data += QString(line.at(i));
                }
                setTurn(data);
                while (true){
                    data = "";
                    line = file.readLine();
                    if (line == "GET THE COUNT\n") break;
                    else {
                    for (int i =0, n = line.size(); i<n-1 ;i++){
                        data += QString(line.at(i));
                    }
                    side.append(data);
                    ++count;
                    }
                }
                for (int i = count; i>0; --i){
                    data = "";
                    line = file.readLine();
                    for (int i =0, n = line.size(); i<n-1 ;i++){
                        data += QString(line.at(i));
                    }
                    piece_name.append(data);
                }
                for (int i = count; i>0; --i){
                    line = file.readLine();
                    if (line.at(0) == '0') posx.append(0);
                    else if (line.at(0) == '1') posx.append(1);
                    else if (line.at(0) == '2') posx.append(2);
                    else if (line.at(0) == '3') posx.append(3);
                    else if (line.at(0) == '4') posx.append(4);
                    else if (line.at(0) == '5') posx.append(5);
                    else if (line.at(0) == '6') posx.append(6);
                    else if (line.at(0) == '7') posx.append(7);
                    else if (line.at(0) == '8') posx.append(8);
                }
                for (int i = count; i>0; --i){
                    line = file.readLine();
                    if (line.at(0) == '0') posy.append(0);
                    else if (line.at(0) == '1') posy.append(1);
                    else if (line.at(0) == '2') posy.append(2);
                    else if (line.at(0) == '3') posy.append(3);
                    else if (line.at(0) == '4') posy.append(4);
                    else if (line.at(0) == '5') posy.append(5);
                    else if (line.at(0) == '6') posy.append(6);
                    else if (line.at(0) == '7') posy.append(7);
                    else if (line.at(0) == '8') posy.append(8);
                }
            }
        }
        file.close ();
         turnDisplay->setPlainText(getTurn() + "'s Turn");
        chess->loadedblack.clear();
        chess->loadedwhite.clear();
        chess->loadwhite(piece_name,side);
        chess->loadblack(piece_name,side);
        chess->loadChessPiece(side, piece_name, posx, posy);
    }
    else{
        for(size_t i =0, n = listP.size(); i < n; i++)
                removeFromScene(listP[i]);
        for(size_t i =0, n = listG.size(); i < n; i++)
                listG[i]->setOpacity(1);
    }
}

void Game::Win_Screen(QString Winner){
    User_was = "Win";
    // Display the win screen
    QGraphicsRectItem* Win_window = new QGraphicsRectItem();
    int winx = 800;
    int winy = 400;
    Win_window->setRect(width()/2- 400, 200, winx, winy);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    Win_window->setBrush(brush);
    Win_window->setOpacity(0.4);
    addToScene(Win_window);
    listG.append(Win_window);

    if (Winner == "WHITE"){
        Image* wink = new Image();
        Image* losek = new Image();
        wink->setPixmap(QPixmap(":/Pieces/Res/pieces/c_wk.svg").scaled(300, 500));
        wink->setPos(200,200);
        losek->setPixmap(QPixmap(":/Pieces/Res/pieces/c_bk.svg").scaled(300, 500));
        losek->setRotation(90);
        losek->setPos(1500,650);
        wink->setPos(200,200);
        addToScene(wink);
        addToScene(losek);
        listG.append(wink);
        listG.append(losek);
    }
    else{
        Image* wink = new Image();
        Image* losek = new Image();
        wink->setPixmap(QPixmap(":/Pieces/Res/pieces/c_bk.svg").scaled(300, 500));
        wink->setPos(200,200);
        losek->setPixmap(QPixmap(":/Pieces/Res/pieces/c_wk.svg").scaled(300, 500));
        losek->setRotation(90);
        losek->setPos(1500,650);
        wink->setPos(200,200);
        addToScene(wink);
        addToScene(losek);
        listG.append(wink);
        listG.append(losek);
    }

    //Show the winner and give option
    QGraphicsTextItem *titleText = new QGraphicsTextItem( "Winner : "+Winner + " Player");
    QFont titleFont("Bradley Hand ITC" , 50);
    titleText->setDefaultTextColor(Qt::white);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 200;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);

    //create return to menu Button
    Button * returnButton = new Button("Main Menu");
    int pxPos = width()/2 - returnButton->boundingRect().width()/2;
    int pyPos = 450;
    returnButton->setPos(pxPos,pyPos);
    connect(returnButton,SIGNAL(clicked()) , this , SLOT(call_menu()));
    addToScene(returnButton);
    listG.append(returnButton);
}

void Game::gameOver(QString Winner){
     removeAll();
     setTurn("WHITE");
     alivePiece.clear();
     chess->reset();
     Win_Screen(Winner);
}

void Game::removeAll(){
    // Remove all the items from the scene
    QList<QGraphicsItem*> itemsList = gameScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}
