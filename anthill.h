#ifndef ANTHILL_H
#define ANTHILL_H

#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>




class AntHill : public QGraphicsPixmapItem
{
public:
    AntHill();
    AntHill(QPixmap pixmap) : QGraphicsPixmapItem(pixmap){};

    ~AntHill(){};



};

#endif // ANTHILL_H
