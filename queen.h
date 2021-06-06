#ifndef QUEEN_H
#define QUEEN_H


#include <ant.h>

class Queen :  public Ant
{

public:
    explicit Queen(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill);

signals:

};

#endif // QUEEN_H
