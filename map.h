#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <iostream>
#include <math.h>
#include <QVBoxLayout>

#include <scene.h>
#include <queen.h>
#include <obstacle.h>
#include <food.h>
#include <anthill.h>
#include <ant.h>
#include <coordinates.h>
#include <egg.h>
#include <larva.h>
#include <warrior.h>

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    std::map<Coord, Cellule*> generateCellDispo(int xStart, int yStart, int xEnd, int yEnd, int newCaseSize);
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

    const int caseSize =  50;
    const int obstacleSize = 100;
    const float imgSize = 0.4f;//scale png
    Coord coord;
    Coord antHillCoord;
    Coord eggCoord;

    std::map<Coord, Cellule*> mapCellDispo; //map each cells to a coord
    std::map<Coord, Cellule*>::iterator cellIt;

    std::map<Coord, Cellule*> mapMove; //map each cells free to move to a coord

    std::map<Coord, Obstacle*> mapObstacle; //map each obstacle to a coord

    std::map<Coord, Food*> mapFood; //map each food to a coord

    std::map<Coord, AntHill*> mapAntHill; //map each AntHill to a coord
    std::map<Coord, AntHill*>::iterator antHillIt; //map each AntHill to a coord
    std::map<Coord, Cellule*> mapCellInAnthill; //map each cells to a coord

    std::map<Warrior*, AntHill*> mapAnt; //map each warrior to a anthill
};

#endif // MAP_H
