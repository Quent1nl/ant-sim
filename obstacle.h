#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <cellule.h>

class Obstacle : public Cellule
{
    public:
    /*!
     * \brief Obstacle
     * \param pixmap, picture to display
     */
    Obstacle(QPixmap pixmap) : Cellule(pixmap){}

    virtual ~Obstacle(){}
};

#endif // OBSTACLE_H
