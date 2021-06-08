#ifndef ANTHILL_H
#define ANTHILL_H

#include <iostream>
#include <QGraphicsScene>

#include <cellule.h>
#include <coordinates.h>
#include <queen.h>

class AntHill : public Cellule
{
public:
    AntHill() ;
    ~AntHill(){};

private :
    std::map<Coord, Cellule*> mapCellInAnthill; //map each cells to a coord

};

#endif // ANTHILL_H
