#include "ant.h"




Ant::Ant(QString antPng, std::map<Coord, Cellule *> &_mapCellDispo, int _nbLigne, Coord &anthillPos, QColor color) :
    mapCellDispo(_mapCellDispo),
    nbLigne(_nbLigne),
    antPng(antPng),
    legPosition(0)
{
    setx(anthillPos.x);
    setY(anthillPos.y);

    //color the ant
    this->antPng2 = this->antPng.left(this->antPng.lastIndexOf('.')) + "2.png";
    this->antP = QPixmap(antPng);
    auto mask = this->antP.createMaskFromColor(QColor(68,114,196), Qt::MaskOutColor)  ;
    QPainter p (&this->antP);
    p.setPen(color);
    p.drawPixmap(this->antP.rect(), mask, mask.rect());
    p.end();

    this->antP2 = QPixmap(this->antPng2);
    auto mask2 = this->antP2.createMaskFromColor(QColor(68,114,196), Qt::MaskOutColor)  ;
    QPainter p2 (&this->antP2);
    p2.setPen(color);
    p2.drawPixmap(this->antP2.rect(), mask2, mask2.rect());
    p2.end();

    setPixmap(this->antP);
    this->setScale(scaleSize);

    QTimer * antTimer = new QTimer(this);
    connect(antTimer, &QTimer::timeout,[=](){
        updatePixmap();
    });

    antTimer->start(80);
}

Ant::Ant(QString antPng, std::map<Coord, Cellule *> &_mapCellDispo, int _nbLigne, Coord &anthillPos, bool _isAnthill, QColor color):
    mapCellDispo(_mapCellDispo),
    nbLigne(_nbLigne),
    isAnthill(_isAnthill),
    antPng(antPng),    
    legPosition(0)
{
    this->scaleSize = 0.08;
    setx(anthillPos.x);
    setY(anthillPos.y);
    //color the ant
    this->antPng2 = this->antPng.left(this->antPng.lastIndexOf('.')) + "2.png";
    setAntP(QPixmap(this->antPng), color);
    setAntP2(QPixmap(this->antPng2), color);
    setPixmap(this->antP);
    this->setScale(scaleSize);

    if(this->isAnthill) {
        this->caseSize = 5;
        this->idAnthill = (this->nbLigne * (x()/caseSize)) + 1 + (y()/caseSize);
    }
    QTimer * antTimer = new QTimer(this);
    connect(antTimer, &QTimer::timeout,[=](){
        updatePixmap();
    });

    antTimer->start(80);
}


Coord Ant::getAdjacent() {

    Coord * coord = new Coord(x(),y(),(this->nbLigne * (x()/caseSize)) + 1 + (y()/caseSize) - this->idAnthill);
    //std::cout<<"current coord x:"<<coord->x<<" coord y:"<<coord->y<<" id: "<<coord->id<<std::endl;
    this->cellIt = this->mapCellDispo.find(*coord);
    //std::cout<< "Coord de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
    Coord co;
    bool foundKey = false;
    // load them in to a list.
    std::list<int> l = {1,2,3,4};
    qreal angle = 200;

//    if (coord->id % this->nbLigne == 0 && (this->nbLigne * (x()/caseSize)) + 1 + (y()/caseSize) != this->idAnthill){
//        l.remove(2);
//    } else if (coord->id % this->nbLigne == 1 && (this->nbLigne * (x()/caseSize)) + 1 + (y()/caseSize) != this->idAnthill){
//        l.remove(1);
//    }
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

                angle = 0;
                //std::cout<< "case en haut de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            }

            break;

        case 2:
            l.remove(*newIt);
            co.id = coord->id + 1;
            if (this->mapCellDispo.find(co) != this->mapCellDispo.end()){
                this->cellIt = this->mapCellDispo.find(co);
                foundKey = true;

                 angle = 180;
                //std::cout<< "case en bas de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            }
            break;

        case 3:
            l.remove(*newIt);
            co.id = coord->id - nbLigne;
            if (this->mapCellDispo.find(co) != this->mapCellDispo.end()){
                this->cellIt = this->mapCellDispo.find(co);
                foundKey = true;
                angle = -90;
                //std::cout<< "case a gauche de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            }
            break;

        case 4:
            l.remove(*newIt);
            co.id = coord->id + nbLigne;
            if (this->mapCellDispo.find(co) != this->mapCellDispo.end()){
                this->cellIt = this->mapCellDispo.find(co);
                foundKey = true;
                angle = 90;
                //std::cout<< "case a droite de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            }
            break;
        }
    } while(!foundKey);
    //std::cout<<"angle :"<<angle;
    if (angle == rotation()){
        rotate(angle , 10);
    }else{
        rotate(angle , 800);
    }


    //std::cout<<"id:"<<this->cellIt->first.id<<std::endl;
    this->newCoord.id = this->cellIt->first.id;
    this->newCoord.x = this->cellIt->first.x;
    this->newCoord.y = this->cellIt->first.y;
    return this->newCoord;


}

const Coord &Ant::getNewCoord() const
{
    return newCoord;
}

void Ant::setAntP(const QPixmap &newAntP, QColor color)
{
    this->antP = newAntP;
    auto mask = this->antP.createMaskFromColor(QColor(68,114,196), Qt::MaskOutColor)  ;
    QPainter p (&this->antP);
    p.setPen(color);
    p.drawPixmap(this->antP.rect(), mask, mask.rect());
    p.end();
}

void Ant::setAntP2(const QPixmap &newAntP2, QColor color)
{
    this->antP2 = newAntP2;
    auto mask2 = this->antP2.createMaskFromColor(QColor(68,114,196), Qt::MaskOutColor)  ;
    QPainter p2 (&this->antP2);
    p2.setPen(color);
    p2.drawPixmap(this->antP2.rect(), mask2, mask2.rect());
    p2.end();
}

 void Ant::moveAnt(){

    this->newCoord = getAdjacent();

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

 void Ant::setAnimationGroup()
 {
     QSequentialAnimationGroup *seqGroupe= new QSequentialAnimationGroup;

     seqGroupe->addAnimation(this->rotationAnimation);
     seqGroupe->addAnimation(this->group);

     seqGroupe->start();

     //std::cout<<"bx : "<<x()<<" y : "<<y()<<std::endl;
     connect(seqGroupe,&QPropertyAnimation::finished,[=](){

         //std::cout<<"ax : "<<x()<<" y : "<<y()<<std::endl;
         moveAnt();

     });
 }

void Ant::updatePixmap()
{
    if (this->legPosition){
        setPixmap(this->antP);
        this->setScale(scaleSize);
        this->legPosition = 0;
    }else{

        setPixmap(this->antP2);
        this->setScale(scaleSize);
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
    //std::cout<<"zx : "<<x()<<" y : "<<y()<<std::endl;
    t.translate(c.x()*scaleSize,c.y()*scaleSize);//go to center of ant
    t.rotate(newRotation);
    t.translate(-c.x()*scaleSize,-c.y()*scaleSize);//go to center of ant
    setTransform(t);
}

void Ant::rotate(const qreal &end, int duration )
{
    this->rotationAnimation = new QPropertyAnimation(this, "rotation",this);
    //std::cout<<" rotation :"<<rotation()<<std::endl;
    this->rotationAnimation->setStartValue(rotation());
    this->rotationAnimation->setEndValue(end);
    //this->rotationAnimation->setEasingCurve(QEasingCurve::Linear);
    this->rotationAnimation->setDuration(duration);
    //std::cout<<"cx : "<<x()<<" y : "<<y()<<std::endl;
    //this->rotationAnimation->start();
}
