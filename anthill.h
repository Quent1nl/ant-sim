#ifndef ANTHILL_H
#define ANTHILL_H

#include <iostream>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsRectItem>

#include <cellule.h>
#include <coordinates.h>
#include <queen.h>
#include <warrior.h>

class AntHill : public QObject, public Cellule
{
    Q_OBJECT
public:
    AntHill() ;
    ~AntHill(){};

    void updateLife(float life);

    int lifeMax = 300;
    int nbAntMax = 20;
    int lifeAnthill = 300;

    void setLifeAnthill(float newLifeAnthill);

    float getLifeAnthill() const;
    void updateBotLife();

    qreal x() const;
    void setx(qreal newX);

    void updateFood();

private :
    std::map<Coord, Cellule*> mapCellInAnthill; //map each cells to a coord
    QGraphicsRectItem * anthillLife;
    QGraphicsRectItem * newAnthillLife;

    QGraphicsRectItem * anthillLifeBot;
    QGraphicsRectItem * newAnthillLifeBot;

    bool collideAnt();

    void animation();

    qreal m_x;

signals:


};

#endif // ANTHILL_H
