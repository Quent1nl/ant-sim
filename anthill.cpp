#include "anthill.h"

AntHill::AntHill(): Cellule(QPixmap(":/assets/green.png")), anthillLife(new QGraphicsRectItem(0,0,127,10,this)), newAnthillLife(new QGraphicsRectItem(0,0,127,10,this)),
anthillLifeBot(new QGraphicsRectItem(0,117,127,10,this)), newAnthillLifeBot(new QGraphicsRectItem(0,117,127,10,this))
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

void AntHill::updateLife(float life)//life of warriors
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
    if (lifeAnthill<0) lifeAnthill = 0;
}
void AntHill::updateBotLife(){
    float life = (getLifeAnthill()/this->lifeMax) *127;
    newAnthillLifeBot->setRect(0,127,life,10);

}

bool AntHill::collideAnt()
{
    QList<QGraphicsItem*> collidingAnt = this->collidingItems();

    foreach (QGraphicsItem * item, collidingAnt){
        Warrior * antItem = dynamic_cast<Warrior*>(item);
        if(antItem) {            
            return true;
        }
    }
    return false;
}



qreal AntHill::x() const
{
    return m_x;
}

void AntHill::setx(qreal newX)
{
    m_x = newX;
}

void AntHill::updateFood()
{
    if (collideAnt()){
        this->lifeAnthill += 20;        
        std::cout<<"food in anthill"<<std::endl;
        if (this->lifeAnthill > this->lifeMax) this->lifeAnthill = this->lifeMax;        
    }
}
