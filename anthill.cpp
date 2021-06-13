#include "anthill.h"

AntHill::AntHill(): Cellule(QPixmap(":/assets/green.png")), anthillLife(new QGraphicsRectItem(0,0,127,10,this)), newAnthillLife(new QGraphicsRectItem(0,0,127,10,this)),
anthillLifeBot(new QGraphicsRectItem(0,127,127,10,this)), newAnthillLifeBot(new QGraphicsRectItem(0,127,127,10,this))
{
    this->setScale(0.78);
    this->setZValue(2);  
    anthillLife->setPen(Qt::NoPen);
    anthillLife->setBrush(Qt::red);
    newAnthillLife->setPen(Qt::NoPen);
    newAnthillLife->setBrush(Qt::green);

    anthillLifeBot->setPen(Qt::NoPen);
    anthillLifeBot->setBrush(Qt::red);
    newAnthillLifeBot->setPen(Qt::NoPen);
    newAnthillLifeBot->setBrush(Qt::green);
}

void AntHill::updateLife(float life)
{
    newAnthillLife->setRect(0,0,life*127,10);

}

float AntHill::getLifeAnthill() const
{
    return lifeAnthill;
}

void AntHill::setLifeAnthill(float newLifeAnthill)
{
    lifeAnthill += newLifeAnthill;
}
void AntHill::updateBotLife(){
    newAnthillLifeBot->setRect(0,127,(getLifeAnthill()/this->lifeMax) *127,10);
}
