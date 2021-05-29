#ifndef ANTHILL_H
#define ANTHILL_H

#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

#include <cellule.h>
#include <food.h>
#include <ant.h>


class AntHill : public QGraphicsPixmapItem
{
public:
    AntHill();
    AntHill(QPixmap pixmap,QGraphicsScene *scene, std::map<Coord, Cellule*>& mapCellDispo , std::map<Coord, Food*>& mapFood, int nbLigne) : QGraphicsPixmapItem(pixmap){
        this->mapCellDispo = mapCellDispo;
        this->mapFood = mapFood;
        this->nbLigne = nbLigne;
        this->scene = scene;

        QPixmap antPng(":/assets/ant.png");

        this->ant = new Ant(antPng);
        this->ant->setScale(0.78);

        ant->setFlag(QGraphicsItem::ItemIsMovable, true);
        ant->setZValue(2);
        this->scene->addItem(ant);
    };
    ~AntHill(){};

    void deplacement();

private:
    std::map<Coord, Cellule*> mapCellDispo;//map each cells to a coord
    std::map<Coord, Food*> mapFood; //map each obstacle to a coord
    int nbLigne;
    QGraphicsScene *scene  ;

    Ant *ant;
    Coord oldCoord;
    Coord newCoord;

};

#endif // ANTHILL_H
