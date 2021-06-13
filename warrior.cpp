#include "warrior.h"

Warrior::Warrior(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, QColor color) : Ant(antPng, _mapCellDispo, _nbLigne, anthillPos, color),
  nbLine(_nbLigne), centerElipse(new QGraphicsEllipseItem(-35,-45,200,200,this))
{
    //centerElipse->setPen(Qt::red);
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

bool Warrior::seeFood()
{
    QList<QGraphicsItem*> seeFood = centerElipse->collidingItems();

    foreach (QGraphicsItem * item, seeFood){
        Food * seeFoodItem = dynamic_cast<Food*>(item);

        if(seeFoodItem){
            //std::cout<<seeFoodItem->pos().x()<<" "<<seeFoodItem->pos().y()<<std::endl;
            this->newCoord.x = seeFoodItem->pos().x();
            this->newCoord.y = seeFoodItem->pos().y();
            this->newCoord.id = (this->nbLine * (this->newCoord.x/50)) + 1 + (this->newCoord.y/50);
            return true;
        }
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

void Warrior::moveAnt(){
   if (!seeFood()){
       this->newCoord = getAdjacent();
   }
   else {
       int id = (this->nbLine * (x()/50)) + 1 + (y()/50);
//       std::cout<<"id : "<<id<<std::endl;
//       std::cout<<"new id :"<<this->newCoord.id<<std::endl;
       int angle = 200;
       int direction =  this->newCoord.id - id;
       //std::cout<<"direction :"<<direction<<std::endl;
       if (direction == -1){
           angle = 0;
           //std::cout<<"direction : top"<<std::endl;
       }
       else if (direction == 1) {
           angle = 180;
           //std::cout<<"direction : bot"<<std::endl;
       }
       else if (direction == -this->nbLine) {
           angle = -90;
           //std::cout<<"direction : gauche"<<std::endl;
       }
       else if (direction == this->nbLine){
           angle = 90;
           //std::cout<<"direction : droite"<<std::endl;
       }
       else if (direction == (this->nbLine-1))
       {
           angle = 45;
           //std::cout<<"direction : top droite"<<std::endl;
       }
       else if (direction == (this->nbLine+1))
       {
           angle = 135;
           //std::cout<<"direction : bot droite"<<std::endl;
       }
       else if (direction == (-this->nbLine-1))  {
           angle = -45;
           //std::cout<<"direction : top gauche"<<std::endl;
       }
       else if (direction == (-this->nbLine+1)) {
           angle = -135;
           //std::cout<<"direction : bot gauche"<<std::endl;
       }
//       //std::cout<<"angle : "<<angle<<std::endl;
//       std::cout<<"rotation : " <<rotation()<<std::endl;

      if (angle == rotation()){
           rotate(angle , 10);
       }/*else if(abs(angle) == 90 || angle == 180 || angle ==0){
           rotate(angle , 800);
       }*/
       else{
           rotate(angle , 800);
       }

   }


   //std::cout<<"nouvelle coord x:"<<this->newCoord.x<<" coord y : "<<this->newCoord.y<<std::endl;

   this->xAnimation = new QPropertyAnimation(this, "x", this);
   this->xAnimation->setStartValue(x());
   this->xAnimation->setEndValue(this->newCoord.x);
   //this->xAnimation->setEasingCurve(QEasingCurve::InQuad);
   this->xAnimation->setDuration(2000);
   //this->xAnimation->start();D


   this->yAnimation = new QPropertyAnimation(this, "y", this);
   this->yAnimation->setStartValue(y());
   this->yAnimation->setEndValue(this->newCoord.y);
   //this->yAnimation->setEasingCurve(QEasingCurve::InQuad);
   this->yAnimation->setDuration(2000);
   //this->yAnimation->start();

   this->group = new QParallelAnimationGroup;
   group->addAnimation(this->xAnimation);
   group->addAnimation(this->yAnimation);
   //group->start();

   setAnimationGroup();


}
