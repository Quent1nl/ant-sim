#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <QObject>

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPropertyAnimation>

#include <warrior.h>

class Pheromone : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(int lifeTime READ lifeTime WRITE setLifeTime)
public:
    explicit Pheromone(int evaporationRate);

    int lifeTime() const;
    void setLifeTime(int newLifeTime);

private:
    QGraphicsEllipseItem * centerElipse;
    bool collidePheromone();
    int m_lifeTime;

    QPropertyAnimation * pheromoneAnimation;

signals:

};

#endif // PHEROMONE_H
