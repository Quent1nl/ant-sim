#ifndef FOOD_H
#define FOOD_H

#include <cellule.h>

class Food : public Cellule
{
public:
    Food() : Cellule(QPixmap(":/assets/food.png")){this->setScale(0.78);};
    ~Food(){};
};

#endif // FOOD_H
