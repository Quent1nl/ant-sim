#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QtDebug>
#include <QGraphicsScene>

#include <ant.h>

class Food : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(int lifeTime READ lifeTime WRITE setLifeTime)
public:

    explicit Food();
    ~Food();;

    int lifeTime() const;
    void setLifeTime(int newLifeTime);


signals:
    void takeFood();
private:
    QPropertyAnimation * foodAnimation;
    int m_lifeTime;
    QGraphicsEllipseItem * centerElipse;

    bool collideWithAnt();
};

#endif // FOOD_H
