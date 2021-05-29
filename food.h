#ifndef FOOD_H
#define FOOD_H

#include <cellule.h>

class Food : public Cellule
{
public:
    Food(QPixmap pixmap) : Cellule(pixmap){};
    ~Food(){};
};

#endif // FOOD_H
