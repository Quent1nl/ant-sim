#include "ant.h"


Ant::Ant():
    legPosition(0)
{
    setPixmap(QPixmap(":/assets/ant.png"));
    //this->setScale(scaleSize);
    QTimer * antTimer = new QTimer(this);
    connect(antTimer, &QTimer::timeout,[=](){
        updatePixmap();
    });

    antTimer->start(150);
}

Ant::Ant(std::map<Coord, Cellule *> &_mapCellDispo, int _nbLigne):
    mapCellDispo(_mapCellDispo),
    nbLigne(_nbLigne),
    legPosition(0)
{
    setPixmap(QPixmap(":/assets/ant.png"));
    this->setScale(scaleSize);


    QTimer * antTimer = new QTimer(this);
    connect(antTimer, &QTimer::timeout,[=](){
        updatePixmap();
    });

    antTimer->start(80);
    this->stack.push(0);
}


Coord Ant::getAdjacent() {

    Coord * coord = new Coord(x(),y(),(this->nbLigne * (x()/100)) + 1 + (y()/100));
    std::cout<<"current coord x:"<<coord->x<<std::endl;
    std::cout<<"current coord y:"<<coord->y<<std::endl;
    std::cout<<"current coord id:"<<coord->id<<std::endl;
    this->cellIt = this->mapCellDispo.find(*coord);
    std::cout<< "Coord de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
    Coord co;
    bool foundKey = false;
    // load them in to a list.
    std::list<int> l = {1,2,3,4};
    int angle;
    do {
        auto it = l.begin();
        auto newIt = std::next(it, (std::rand() % l.size())+1 );//select a random cell available
        switch(*newIt){
        case 1:
            l.remove(*newIt);
            co.id = coord->id - 1;
            if (this->mapCellDispo.find(co) != this->mapCellDispo.end()){
                this->cellIt = this->mapCellDispo.find(co);
                foundKey = true;

                angle = 0 - this->stack.top();
                this->stack.push(0);
                this->stack.pop();

                std::cout<< "case en haut de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            }

            break;

        case 2:
            l.remove(*newIt);
            co.id = coord->id + 1;
            if (this->mapCellDispo.find(co) != this->mapCellDispo.end()){
                this->cellIt = this->mapCellDispo.find(co);
                foundKey = true;

                angle = 2 - this->stack.top();
                this->stack.push(2);
                this->stack.pop();

                std::cout<< "case en bas de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            }
            break;

        case 3:
            l.remove(*newIt);
            co.id = coord->id - nbLigne;
            if (this->mapCellDispo.find(co) != this->mapCellDispo.end()){
                this->cellIt = this->mapCellDispo.find(co);
                foundKey = true;

                angle = 3 - this->stack.top();
                if (angle == 3) angle = -1;
                this->stack.push(3);
                this->stack.pop();

                std::cout<< "case a gauche de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            }
            break;

        case 4:
            l.remove(*newIt);
            co.id = coord->id + nbLigne;
            if (this->mapCellDispo.find(co) != this->mapCellDispo.end()){
                this->cellIt = this->mapCellDispo.find(co);
                foundKey = true;

                angle = 1 - this->stack.top();
                this->stack.push(1);
                this->stack.pop();

                std::cout<< "case a droite de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            }
            break;
        }
    } while(!foundKey);
    std::cout<<"angle :"<<angle;
    rotate(90 * angle);
    std::cout<<this->stack.top();
    std::cout<<"id:"<<this->cellIt->first.id<<std::endl;
    this->newCoord.id = this->cellIt->first.id;
    this->newCoord.x = this->cellIt->first.x;
    this->newCoord.y = this->cellIt->first.y;
    return this->newCoord;


}

void Ant::moveAnt(){

    setx(100);
    setY(200);

    this->newCoord = getAdjacent();

    std::cout<<"nouvelle coord x:"<<this->newCoord.x<<std::endl;
    std::cout<<"nouvelle coord y:"<<this->newCoord.y<<std::endl;

    this->xAnimation = new QPropertyAnimation(this, "x", this);
    this->xAnimation->setStartValue(scenePos().x());
    this->xAnimation->setEndValue(this->newCoord.x);
    //this->xAnimation->setEasingCurve(QEasingCurve::InQuad);
    this->xAnimation->setDuration(5000);
    //this->xAnimation->start();


    this->yAnimation = new QPropertyAnimation(this, "y", this);
    this->yAnimation->setStartValue(scenePos().y());
    this->yAnimation->setEndValue(this->newCoord.y);
    //this->yAnimation->setEasingCurve(QEasingCurve::InQuad);
    this->yAnimation->setDuration(5000);
    //this->yAnimation->start();

    QParallelAnimationGroup * group = new QParallelAnimationGroup;
    group->addAnimation(this->xAnimation);
    group->addAnimation(this->yAnimation);
    //group->start();

    QSequentialAnimationGroup *seqGroupe= new QSequentialAnimationGroup;

    seqGroupe->addAnimation(this->rotationAnimation);
    seqGroupe->addAnimation(group);

    seqGroupe->start();
}

void Ant::updatePixmap()
{
    if (this->legPosition){
        setPixmap(QPixmap(":/assets/ant.png"));
        //this->setScale(scaleSize);
        this->legPosition = 0;
    }else{
        setPixmap(QPixmap(":/assets/ant2.png"));
        //this->setScale(scaleSize);
        this->legPosition = 1;
    }
}


qreal Ant::x() const
{
    //std::cout<<"m_x : "<<this->m_x<<std::endl;
    return this->m_x;
}

void Ant::setx(qreal newX)
{
    moveBy(newX - this->m_x,0);
    this->m_x = newX;
    //std::cout<<"setter m_x : "<<this->m_x<<std::endl;
}

qreal Ant::y() const
{
    //std::cout<<"m_y : "<<this->m_y<<std::endl;
    return this->m_y;
}

void Ant::setY(qreal newY)
{
    moveBy(0, newY - this->m_y);
    this->m_y = newY;
    //std::cout<<"setter m_y : "<<this->m_y<<std::endl;
}

const qreal &Ant::rotation() const
{
    return m_rotation;
}

void Ant::setRotation(const qreal &newRotation)
{
    m_rotation = newRotation;

    QPointF c = boundingRect().center();//get center of ant
    QTransform t ;
    //std::cout<<"c.x : "<<c.x()<<" c.y : "<<c.y()<<std::endl;
    t.translate(c.x()*scaleSize,c.y()*scaleSize);//go to center of ant
    t.rotate(newRotation);
    t.translate(-c.x()*scaleSize,-c.y()*scaleSize);//go to center of ant
    setTransform(t);
}

void Ant::rotate(const qreal &end)
{
    this->rotationAnimation = new QPropertyAnimation(this, "rotation",this);
    std::cout<<"rotation :"<<rotation()<<std::endl;
    this->rotationAnimation->setStartValue(rotation());
    this->rotationAnimation->setEndValue(end);
    //this->rotationAnimation->setEasingCurve(QEasingCurve::Linear);
    this->rotationAnimation->setDuration(1000);
    //this->rotationAnimation->start();
}
