#include "queen.h"

Queen::Queen(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill) : Ant(antPng, _mapCellDispo, _nbLigne, anthillPos, isAnthill)
{

}
