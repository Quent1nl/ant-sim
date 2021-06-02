#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>
#include <QGraphicsPixmapItem>


class Cellule : public QGraphicsPixmapItem
{

public:
    Cellule(QPixmap pixmap): QGraphicsPixmapItem(pixmap){};
    virtual ~Cellule(){};


};

#endif // CELLULE_H
