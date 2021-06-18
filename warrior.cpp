#include "warrior.h"

Warrior::Warrior(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, QColor color, int evaporationRate) : Ant(antPng, _mapCellDispo, _nbLigne, anthillPos, color),
  nbLine(_nbLigne), evaporationRate(evaporationRate), centerElipse(new QGraphicsEllipseItem(-110,-110, 350,350,this)), miniElipse(new QGraphicsEllipseItem(50,50,40,40,this))
{
    centerElipse->setPen(Qt::NoPen);
    miniElipse->setPen(Qt::NoPen);
    //centerElipse->setPen(Qt::red);
    this->xAnthill = anthillPos.x;
    this->yAnthill = anthillPos.y;
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
    QList<QGraphicsItem*> collidingFood = miniElipse->collidingItems();

    foreach (QGraphicsItem * item, collidingFood){
        Food * foodItem = dynamic_cast<Food*>(item);
        if(foodItem) {
            //std::cout<<"Collide with food"<<std::endl;
            this->gotFood = true;
            return true;
        }
    }
    return false;
}

bool Warrior::collideWithAnthill()
{
    if (this->pos().x() == this->xAnthill && this->pos().y() == this->yAnthill){
        if (this->gotFood){

            emit updateFood();
            this->gotFood = false;
            //std::cout<<"got foodzdzd ? "<<this->gotFood<<std::endl;
        }
        return true;
    }
    return false;
//    QList<QGraphicsItem*> collidingAnthill = miniElipse->collidingItems();

//    foreach (QGraphicsItem * item, collidingAnthill){
//        AntHill * anthillItem = dynamic_cast<AntHill*>(item);
//        if(anthillItem) {
//            std::cout<<"collide with anthill"<<std::endl;
//            if (this->gotFood){

//                emit updateFood();
//                this->gotFood = false;
//            //std::cout<<"got foodzdzd ? "<<this->gotFood<<std::endl;
//            }
//            return true;
//        }
//    }
//    return false;
}

bool Warrior::seeFood()
{
    QList<QGraphicsItem*> seeFood = centerElipse->collidingItems();

    foreach (QGraphicsItem * item, seeFood){
        Food * seeFoodItem = dynamic_cast<Food*>(item);

        if(seeFoodItem){
//            std::cout<<"see food"<<std::endl;
            //std::cout<<seeFoodItem->pos().x()<<" "<<seeFoodItem->pos().y()<<std::endl;
            this->newCoord.x = seeFoodItem->pos().  x();
            this->newCoord.y = seeFoodItem->pos().y();
            this->newCoord.id = (this->nbLine * (this->newCoord.x/50)) + 1 + (this->newCoord.y/50);
            return true;
        }
    }
    return false;
}

bool Warrior::seePheromone()
{
    QList<QGraphicsItem*> seePheromone = centerElipse->collidingItems();

    foreach (QGraphicsItem * item, seePheromone){
        Pheromone * seePheromoneItem = dynamic_cast<Pheromone*>(item);

        if(seePheromoneItem && (seePheromoneItem->pos().x()!= x()) && (seePheromoneItem->pos().y()!= y()) && (seePheromoneItem->pos().x()!=this->xPrevious) && (seePheromoneItem->pos().y() != this->yPrevious)){ //for current pheromones

            //std::cout<<"see phero"<<std::endl;
            //std::cout<<seePheromoneItem->pos().x()<<" "<<this->xPrevious<<" y : "<<seePheromoneItem->pos().y()<<" "<<this->yPrevious<<std::endl;
           // seePheromoneItem->pos().x()!=this->xPrevious && seePheromoneItem->pos().y() != this->yPrevious
            this->newCoord.x = seePheromoneItem->pos().x();
            this->newCoord.y = seePheromoneItem->pos().y();
            this->newCoord.id = (this->nbLine * (this->newCoord.x/50)) + 1 + (this->newCoord.y/50);

            this->xPrevious = seePheromoneItem->pos().x();
            this->yPrevious = seePheromoneItem->pos().y();
            return true;
        }
    }
    return false;
}

bool Warrior::seeAnthill()
{
    QList<QGraphicsItem*> seeAnthill = centerElipse->collidingItems();

    foreach (QGraphicsItem * item, seeAnthill){
        AntHill * seeAnthillItem = dynamic_cast<AntHill*>(item);
        //std::cout<<"see anthill 0"<<std::endl;
        if(seeAnthillItem /*&&*/ /*seeAnthillItem->pos().x()!= x() && seeAnthillItem->pos().y()!= y()*/){
//            std::cout<<"see anthill"<<std::endl;
            this->newCoord.x = seeAnthillItem->pos().x();
            this->newCoord.y = seeAnthillItem->pos().y();
            this->newCoord.id = (this->nbLine * (this->newCoord.x/50)) + 1 + (this->newCoord.y/50);
            return true;
        }
    }
    return false;
}





void Warrior::setx(qreal newX)
{
    //seePheromone();
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

void Warrior::setGotFood(bool state)
{
    this->gotFood = state;
}

bool Warrior::getGotFood() const
{
    return gotFood;
}

void Warrior::insertPheromone()
{
    Pheromone * pheromone = new Pheromone(this->evaporationRate);
    pheromone->setPos(this->x(), this->y());
    scene()->addItem(pheromone);
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
//    std::cout<<"got food = "<<getGotFood()<<std::endl;
    if (!this->gotFood) insertPheromone();
    collideWithAnthill();
    if ((!this->gotFood && !seeFood()) || (this->gotFood && !seePheromone() && !seeAnthill() && !seeFood()) ) {
//        std::cout<<"adjacent movement"<<std::endl;
        this->newCoord = getAdjacent();
    }
    else {
        if (this->gotFood){
            if(seeAnthill()){
                //std::cout<<"see anthill 0"<<std::endl;
//                std::cout<<"got food and see anthill "<<std::endl;
                //seeAnthill();
            }
            else if (seePheromone()) {
                //std::cout<<"see phero 1"<<std::endl;
                //seePheromone();
            }
            else if(seeFood()) {
                //std::cout<<"see food 2"<<std::endl;
                //seeFood();
            }
        }
        else if (!this->gotFood){
            //std::cout<<"see food 4"<<std::endl;
            //seeFood();
        }

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
   this->xAnimation->setDuration(3000);
   //this->xAnimation->start();D


   this->yAnimation = new QPropertyAnimation(this, "y", this);
   this->yAnimation->setStartValue(y());
   this->yAnimation->setEndValue(this->newCoord.y);
   //this->yAnimation->setEasingCurve(QEasingCurve::InQuad);
   this->yAnimation->setDuration(3000);
   //this->yAnimation->start();

   this->group = new QParallelAnimationGroup;
   group->addAnimation(this->xAnimation);
   group->addAnimation(this->yAnimation);
   //group->start();

   setAnimationGroup();


}
