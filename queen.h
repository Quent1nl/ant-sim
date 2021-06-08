#ifndef QUEEN_H
#define QUEEN_H


#include <ant.h>


class Queen :  public Ant
{
    Q_OBJECT
public:
    explicit Queen(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill, QColor color);
    void setAnimationGroup() override;

private:
    int newEgg = 0;

signals:
    void generateEgg() ;

};

#endif // QUEEN_H
