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
    explicit Warrior(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, QColor color, int evaporationRate);
    int getLife() const;
    void moveAnt() override;


private:
    int life = 10;
    int nbLine = 0;
    int evaporationRate;

    int m_rip;
    bool gotFood = false;

    int xPrevious=-10;
    int yPrevious=-10;

    int xAnthill = 0, yAnthill = -1;

    QPropertyAnimation * ripAnimation;

    QGraphicsEllipseItem * centerElipse;
    QGraphicsEllipseItem * miniElipse;

    bool collideWithFood();
    bool collideWithAnthill();
    bool seeFood();
    bool seePheromone();
    bool seeAnthill();

    void setx(qreal newX) override;
    void setY(qreal newY) override;

    void insertPheromone();
    void setAnimationGroup() override;

    void setLife(int newLife);

    int rip() const;
    void setRip(int newRip);

    bool getGotFood() const;
    void setGotFood(bool state);

signals:
    void warriorDead();
    void updateFood();
};

#endif // WARRIOR_H
