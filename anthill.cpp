#include "anthill.h"

AntHill::AntHill(std::map<Coord , Cellule*>& mapCellDispo , std::map<Coord, Food*>& mapFood ){
    this->mapCellDispo = mapCellDispo;
    this->mapFood = mapFood;
};
