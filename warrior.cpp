#include "warrior.h"

Warrior::Warrior(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, QColor color) : Ant(antPng, _mapCellDispo, _nbLigne, anthillPos, color)
{

}

void Warrior::setAnimationGroup()
{
    QSequentialAnimationGroup *seqGroupe= new QSequentialAnimationGroup;

    seqGroupe->addAnimation(this->rotationAnimation);
    seqGroupe->addAnimation(this->group);

    seqGroupe->start();

    //std::cout<<"bx : "<<x()<<" y : "<<y()<<std::endl;
    connect(seqGroupe,&QPropertyAnimation::finished,[=](){
        //std::cout<<"life: "<<this->life<<std::endl;
        if (this->life-- == 0){
            emit warriorDead();
            seqGroupe->stop();

            setAntP(QPixmap(":/assets/tombstone.png"),Qt::transparent);
            setAntP2(QPixmap(":/assets/tombstone.png"),Qt::transparent);
            this->ripAnimation = new QPropertyAnimation(this, "rip", this);
            this->ripAnimation->setStartValue(0);
            this->ripAnimation->setEndValue(5);
            //this->xAnimation->setEasingCurve(QEasingCurve::InQuad);
            this->ripAnimation->setDuration(5000);
            this->ripAnimation->start();
            connect(this->ripAnimation,&QPropertyAnimation::finished,[=](){
                scene()->removeItem(this);
                delete this;
            });

        }else{
            //std::cout<<"ax : "<<x()<<" y : "<<y()<<std::endl;
            moveAnt();
        }


    });
}

int Warrior::getLife() const
{
    return life;
}

void Warrior::setLife(int newLife)
{
    this->life = newLife;
    //std::cout<<"new life"<<life<<std::endl;
}

bool Warrior::collideWithFood()
{
    QList<QGraphicsItem*> collidingFood = this->collidingItems();

    foreach (QGraphicsItem * item, collidingFood){
        Food * foodItem = dynamic_cast<Food*>(item);
        if(foodItem) return true;
    }
    return false;
}

void Warrior::setx(qreal newX)
{
    if (collideWithFood()) setLife(20);
    moveBy(newX - this->m_x,0);
    this->m_x = newX;
    //std::cout<<"setter m_x : "<<this->m_x<<std::endl;
}


void Warrior::setY(qreal newY)
{
    if (collideWithFood()) setLife(20);
    moveBy(0, newY - this->m_y);
    this->m_y = newY;
    //std::cout<<"setter m_y : "<<this->m_y<<std::endl;
}

int Warrior::rip() const
{
    return m_rip;
}

void Warrior::setRip(int newRip)
{
    m_rip = newRip;
}
