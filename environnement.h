#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <QWidget>
#include <QtWidgets>
#include <map>
#include <QGraphicsView>
#include <mainwindow.h>//pour le coord, à enlever lorsque l'on aura une classe coord

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

    QGraphicsView *view; //verifier si le pointer doit être delete
    QGraphicsScene *scene;

private:
    Ui::environnement *ui;
};

#endif // ENVIRONNEMENT_H
