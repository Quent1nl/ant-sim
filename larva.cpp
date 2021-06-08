#include "larva.h"

Larva::Larva(QString antPng, std::map<Coord, Cellule *> &_mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill, QColor color): Ant(antPng, _mapCellDispo, _nbLigne, anthillPos, isAnthill, color)
{
    this->larvaAnimation = new QPropertyAnimation(this, "lifeTime", this);
    this->larvaAnimation->setStartValue(0);
    this->larvaAnimation->setEndValue(5);
    //this->xAnimation->setEasingCurve(QEasingCurve::InQuad);
    this->larvaAnimation->setDuration(10000);

    connect(this->larvaAnimation,&QPropertyAnimation::finished,[=](){
        emit generateAnt();
        scene()->removeItem(this);
        delete this;
    });
    this->larvaAnimation->start();
}

int Larva::lifeTime() const
{
    return m_lifeTime;
}

void Larva::setLifeTime(int newLifeTime)
{
    m_lifeTime = newLifeTime;
}
