#ifndef WARRIOR_H
#define WARRIOR_H

#include <ant.h>
#include <QGraphicsScene>
#include <food.h>
#include <QPropertyAnimation>

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

private:
    int life = 10;

    bool collideWithFood();

    void setx(qreal newX) override;
    void setY(qreal newY) override;

    int m_rip;

    QPropertyAnimation * ripAnimation;

signals:
    void warriorDead();
};

#endif // WARRIOR_H
