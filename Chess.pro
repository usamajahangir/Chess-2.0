QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bishop.cpp \
    Button.cpp \
    Chess_Board.cpp \
    Chess_Box.cpp \
    Chess_Piece.cpp \
    Game.cpp \
    Image.cpp \
    King.cpp \
    Knight.cpp \
    Main.cpp \
    Pawn.cpp \
    Queen.cpp \
    Rook.cpp

HEADERS += \
    Bishop.h \
    Button.h \
    Chess_Board.h \
    Chess_Box.h \
    Chess_Piece.h \
    Game.h \
    Image.h \
    King.h \
    Knight.h \
    Pawn.h \
    Queen.h \
    Rook.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
