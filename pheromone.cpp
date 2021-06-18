#include "pheromone.h"

Pheromone::Pheromone(int evaporationRate)
{
    setPixmap(QPixmap(":/assets/dot.png"));
    this->setScale(0.4);
    this->setZValue(2);
    this->pheromoneAnimation = new QPropertyAnimation(this, "lifeTime", this);
    this->pheromoneAnimation->setStartValue(0);
    this->pheromoneAnimation->setEndValue(5);
    //this->xAnimation->setEasingCurve(QEasingCurve::InQuad);
    this->pheromoneAnimation->setDuration(30000 * (evaporationRate+2));


    connect(this->pheromoneAnimation,&QPropertyAnimation::finished,[=](){
        //std::cout<<"food expired"<<std::endl;
        scene()->removeItem(this);
        delete this;
    });
    this->pheromoneAnimation->start();
}

bool Pheromone::collidePheromone()
{
    QList<QGraphicsItem*> collidingPheromone = this->collidingItems();

    foreach (QGraphicsItem * item, collidingPheromone){
        Warrior * collidingPheromoneItem = dynamic_cast<Warrior*>(item);
        if(collidingPheromoneItem && collidingPheromoneItem->x() != x() && collidingPheromoneItem->y() != y()) {
            return true;
        }
    }
    return false;
}

int Pheromone::lifeTime() const
{

    return m_lifeTime;
}

void Pheromone::setLifeTime(int newLifeTime)
{
//    if (collidePheromone()){
//        scene()->removeItem(this);
//        delete this;
//    }

    m_lifeTime = newLifeTime;
}
