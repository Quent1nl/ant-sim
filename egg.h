#ifndef EGG_H
#define EGG_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

#include <ant.h>

class Egg : public Ant
{
    Q_OBJECT
    Q_PROPERTY(int lifeTime READ lifeTime WRITE setLifeTime)
public:
    explicit Egg(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill, QColor color);

signals:
    void generateLarva() ;

private:
    int m_lifeTime;
    QPropertyAnimation * eggAnimation;

    int lifeTime() const;
    void setLifeTime(int newLifeTime);
};

#endif // EGG_H
