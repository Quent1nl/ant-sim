#ifndef LARVA_H
#define LARVA_H

#include <QObject>
#include <ant.h>
#include <QPropertyAnimation>

class Larva : public Ant
{
    Q_OBJECT
    Q_PROPERTY(int lifeTime READ lifeTime WRITE setLifeTime)
    int m_lifeTime;

public:
    explicit Larva(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill, QColor color);

    int lifeTime() const;
    void setLifeTime(int newLifeTime);
    QPropertyAnimation * larvaAnimation;

signals:
    void generateAnt();
};

#endif // LARVA_H
