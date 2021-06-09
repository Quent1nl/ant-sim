#include "anthill.h"

AntHill::AntHill(): Cellule(QPixmap(":/assets/green.png")), anthillLife(new QGraphicsRectItem(0,0,127,10,this)), newAnthillLife(new QGraphicsRectItem(0,0,127,10,this)){
    this->setScale(0.78);
    this->setZValue(2);  
    anthillLife->setPen(Qt::NoPen);
    anthillLife->setBrush(Qt::red);
    newAnthillLife->setPen(Qt::NoPen);
    newAnthillLife->setBrush(Qt::green);
}

void AntHill::updateLife(float life)
{
    newAnthillLife->setRect(0,0,life*127,10);
}
