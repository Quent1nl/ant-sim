#include "queen.h"

Queen::Queen(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill, QColor color) : Ant(antPng, _mapCellDispo, _nbLigne, anthillPos, isAnthill, color)
{

}

void Queen::setAnimationGroup()
{
    QSequentialAnimationGroup *seqGroupe= new QSequentialAnimationGroup;

    seqGroupe->addAnimation(this->rotationAnimation);
    seqGroupe->addAnimation(this->group);

    seqGroupe->start();

    //std::cout<<"bx : "<<x()<<" y : "<<y()<<std::endl;
    connect(seqGroupe,&QPropertyAnimation::finished,[=](){
        //std::cout<<"egg: "<<this->newEgg<<std::endl;
        if (this->newEgg++ == 5){
            this->newEgg = 0;
            emit generateEgg();
        }
        //std::cout<<"ax : "<<x()<<" y : "<<y()<<std::endl;
        moveAnt();

    });
}
