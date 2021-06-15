#ifndef WARRIOR_H
#define WARRIOR_H

#include <ant.h>
#include <QGraphicsScene>
#include <food.h>
#include <QPropertyAnimation>
#include <pheromone.h>
#include <anthill.h>

class Warrior : public Ant
{
    Q_OBJECT
    Q_PROPERTY(int rip READ rip WRITE setRip)
public:
    explicit Warrior(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, QColor color);
    void setAnimationGroup() override;

    int getLife() const;
    void setLife(int newLife);

    int rip() const;
    void setRip(int newRip);
    void moveAnt() override;
    bool getGotFood() const;
    void setGotFood(bool state);

private:
    int life = 10;
    int nbLine = 0;
    bool collideWithFood();
    bool seeFood();
    bool seePheromone();
    bool seeAnthill();

    void setx(qreal newX) override;
    void setY(qreal newY) override;

    int m_rip;
    bool gotFood = false;

    void insertPheromone();
    QPropertyAnimation * ripAnimation;

    QGraphicsEllipseItem * centerElipse;
signals:
    void warriorDead();
};

#endif // WARRIOR_H
