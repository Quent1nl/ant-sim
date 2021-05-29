#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <QWidget>
#include <QtWidgets>
#include <QGraphicsView>
#include <iostream>
#include <string>
#include <QPainter>

#include <mainwindow.h>//pour le coord, à enlever lorsque l'on aura une classe coord
#include <cellule.h>
#include <obstacle.h>
#include <food.h>
#include <anthill.h>



namespace Ui {
class environnement;
}


class environnement : public QWidget
{
    Q_OBJECT

public:
    explicit environnement(QWidget *parent = nullptr);
    explicit environnement(Coord coord, QWidget *parent = nullptr);
    ~environnement();

    void showMap();
    void generateObstacle(Coord& coord);
    void generateFood(Coord& coord);
    void generateFloor();
    void generateAntHill(Coord& coord);

private:
    Ui::environnement *ui;
    QGraphicsView *view; //verifier si le pointer doit être delete
    QGraphicsScene *scene;

    const int caseSize =  100;
    const float imgSize = 0.78f;//scale png

    std::map<Coord, Cellule*> mapCellDispo; //map each cells to a coord
    std::map<Coord, Cellule*>::iterator cellIt;

    std::map<Coord, Obstacle*> mapObstacle; //map each obstacle to a coord

    std::map<Coord, Food*> mapFood; //map each obstacle to a coord

    std::map<Coord, AntHill*> mapAntHill; //map each obstacle to a coord

    Coord coord;
};

#endif // ENVIRONNEMENT_H
