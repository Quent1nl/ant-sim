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

    int lifeMax = 300;
    int nbAntMax = 20;
    int lifeAnthill = 300;

    void setLifeAnthill(float newLifeAnthill);

    float getLifeAnthill() const;
    void updateBotLife();

private :
    std::map<Coord, Cellule*> mapCellInAnthill; //map each cells to a coord
    QGraphicsRectItem * anthillLife;
    QGraphicsRectItem * newAnthillLife;

    QGraphicsRectItem * anthillLifeBot;
    QGraphicsRectItem * newAnthillLifeBot;

};

#endif // ANTHILL_H
