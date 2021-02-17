#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>
#include "Game.h"

extern Game* game;

Button::Button(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent){
    //draw the rectangle for button
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    setBrush(brush);

    // Set opacity
    this->setOpacity(qreal(0.7));

    //draw Text on the rectangle button
    text = new QGraphicsTextItem(name,this);
    QFont text_font("Bradley Hand ITC" , 20);
    text->setFont(text_font);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    game->listG.append(text);

    text->setDefaultTextColor(Qt::black);

    //Allow responding to hover
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event)
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    //change color on hover event
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    }
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //change color on hover event
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    setBrush(brush);
    }
}
