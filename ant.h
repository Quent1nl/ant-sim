#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <QWidget>
#include <windows.h>

#include <cellule.h>
#include <food.h>
#include <Coordinates.h>



class Ant: public QGraphicsPixmapItem
{
public:
    Ant(){};
    Ant(QPixmap pixmap, std::map<Coord, Cellule*>& mapCellDispo , std::map<Coord, Food*>& mapFood, int nbLigne): QGraphicsPixmapItem(pixmap){
        this->mapCellDispo = mapCellDispo;
        this->mapFood = mapFood;
        this->nbLigne = nbLigne;        

    };
    //Ant(const Ant &ant);
    ~Ant(){};

    Coord getAdjacent(const Coord& coord );
    void moveAnt();

    std::map<Coord, Cellule*>::iterator cellIt;

private:
    std::map<Coord, Cellule*> mapCellDispo;//map each cells to a coord
    std::map<Coord, Food*> mapFood; //map each obstacle to a coord
    int nbLigne;    

    Coord oldCoord;
    Coord newCoord;
};

#endif // ANT_H
