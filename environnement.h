#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <QWidget>
#include <QtWidgets>
#include <QGraphicsView>
#include <iostream>
#include <string>

#include <mainwindow.h>//pour le coord, à enlever lorsque l'on aura une classe coord
#include <cellule.h>
#include <obstacle.h>

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

private:
    Ui::environnement *ui;
    QGraphicsView *view; //verifier si le pointer doit être delete
    QGraphicsScene *scene;
    std::map<Coord, Cellule*> mapCellule; //map each cells to a coord
};

#endif // ENVIRONNEMENT_H
