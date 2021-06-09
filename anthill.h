#ifndef ANTHILL_H
#define ANTHILL_H

#include <iostream>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsRectItem>

#include <cellule.h>
#include <coordinates.h>
#include <queen.h>

class AntHill : public Cellule
{
public:
    AntHill() ;
    ~AntHill(){};

    void updateLife(float life);

private :
    std::map<Coord, Cellule*> mapCellInAnthill; //map each cells to a coord
    QGraphicsRectItem * anthillLife;
    QGraphicsRectItem * newAnthillLife;

};

#endif // ANTHILL_H
