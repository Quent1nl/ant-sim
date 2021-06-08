#include "egg.h"

Egg::Egg(QString antPng, std::map<Coord, Cellule *> &_mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill, QColor color): Ant(antPng, _mapCellDispo, _nbLigne, anthillPos, isAnthill, color)
{
    this->eggAnimation = new QPropertyAnimation(this, "lifeTime", this);
    this->eggAnimation->setStartValue(0);
    this->eggAnimation->setEndValue(5);
    //this->xAnimation->setEasingCurve(QEasingCurve::InQuad);
    this->eggAnimation->setDuration(7000);

    connect(this->eggAnimation,&QPropertyAnimation::finished,[=](){
        emit generateLarva();
        scene()->removeItem(this);
        delete this;        
    });
    this->eggAnimation->start();

}

int Egg::lifeTime() const
{
    return m_lifeTime;
}

void Egg::setLifeTime(int newLifeTime)
{
    m_lifeTime = newLifeTime;
}
