#include "food.h"




Food::Food() :
    centerElipse(new QGraphicsEllipseItem(50,50,40,40,this))
{
    centerElipse->setPen(Qt::NoPen);
    setPixmap(QPixmap(":/assets/food.png"));
    this->setZValue(2);
    this->foodAnimation = new QPropertyAnimation(this, "lifeTime", this);
    this->foodAnimation->setStartValue(0);
    this->foodAnimation->setEndValue(5);
    //this->xAnimation->setEasingCurve(QEasingCurve::InQuad);
    this->foodAnimation->setDuration(25000);

    connect(this->foodAnimation,&QPropertyAnimation::finished,[=](){
        emit takeFood();
        //std::cout<<"food expired"<<std::endl;
        scene()->removeItem(this);
        delete this;
    });
    this->foodAnimation->start();
}

Food::~Food(){
    //qDebug() << "Deleted food";
}

int Food::lifeTime() const
{
    return m_lifeTime;
}

void Food::setLifeTime(int newLifeTime)
{
    if (collideWithAnt()){
        emit takeFood();
        scene()->removeItem(this);
        delete this;
    }
    m_lifeTime = newLifeTime;
}


bool Food::collideWithAnt()
{
    QList<QGraphicsItem*> collidingAnt = this->centerElipse->collidingItems();

    foreach (QGraphicsItem * item, collidingAnt){
        Ant * antItem = dynamic_cast<Ant*>(item);
        if(antItem) return true;
    }
    return false;
}
