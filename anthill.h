#ifndef ANTHILL_H
#define ANTHILL_H

#include <iostream>
#include <cellule.h>
#include <food.h>

class AntHill
{
public:
    AntHill();
    AntHill(std::map<Coord, Cellule*>& mapCellDispo , std::map<Coord, Food*>& mapFood );

    ~AntHill(){};

private:
    std::map<Coord, Cellule*> mapCellDispo;//map each cells to a coord
    std::map<Coord, Food*> mapFood; //map each obstacle to a coord
};

#endif // ANTHILL_H
