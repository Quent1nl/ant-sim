#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <cellule.h>

class Obstacle : public Cellule
{
    public:

    Obstacle(QPixmap pixmap) : Cellule(pixmap){}

    ~Obstacle(){}
};

#endif // OBSTACLE_H
