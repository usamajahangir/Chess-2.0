#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Image : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Image(QGraphicsItem* parent = 0);
};
#endif // IMAGE_H
