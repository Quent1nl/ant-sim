#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <iostream>
#include <math.h>
#include <QVBoxLayout>

#include <scene.h>
#include <obstacle.h>
#include <food.h>
#include <anthill.h>
#include <ant.h>
#include <coordinates.h>

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    void generateCellDispo();
    void generateObstacle();
    void generateIntialFood();
    void generateFood();
    void generateFloor();
    void generateAntHill();

private slots:
    void on_playButton_clicked();

private:
    Ui::Map *ui;
    Scene * scene;

    const int caseSize =  100;
    const float imgSize = 0.78f;//scale png
    Coord coord;


    std::map<Coord, Cellule*> mapCellDispo; //map each cells to a coord
    std::map<Coord, Cellule*>::iterator cellIt;

    std::map<Coord, Cellule*> mapMove; //map each cells free to move to a coord

    std::map<Coord, Obstacle*> mapObstacle; //map each obstacle to a coord

    std::map<Coord, Food*> mapFood; //map each food to a coord

    std::map<Coord, AntHill*> mapAntHill; //map each AntHill to a coord
    std::map<Coord, AntHill*>::iterator antHillIt; //map each AntHill to a coord

    std::map<Ant*, AntHill*> mapAnt; //map each ant to a anthill
};

#endif // MAP_H
