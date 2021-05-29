#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <QWidget>
#include <windows.h>


#include <cellule.h>


class Ant: public QGraphicsPixmapItem
{
public:
    Ant(){};
    Ant(QPixmap pixmap): QGraphicsPixmapItem(pixmap){};
    //Ant(const Ant &ant);
    ~Ant(){};

    Coord getAdjacent(Coord& coord, std::map<Coord, Cellule*>& mapCellDispo, int nbLigne);
    void moveAnt(Coord& oldCoord,Coord& newCoord );

    std::map<Coord, Cellule*>::iterator cellIt;

};

#endif // ANT_H
