#ifndef ANTHILL_H
#define ANTHILL_H

#include <iostream>
#include <cellule.h>




class AntHill : public Cellule
{
public:
    AntHill() : Cellule(QPixmap(":/assets/green.png")){this->setScale(0.78);};


    ~AntHill(){};



};

#endif // ANTHILL_H
