#ifndef CELLULE_H
#define CELLULE_H

#include <iostream>
#include <QGraphicsPixmapItem>

struct Coord{
    int x=10, y=10, id = 0;
    Coord(){};
    Coord(int x, int y, int id) : x(x), y(y), id(id) {};
};
inline bool operator<(const Coord& coord1, const Coord& coord2) { return  coord1.id < coord2.id; }

class Cellule : public QGraphicsPixmapItem
{

public:
    Cellule(QPixmap pixmap): QGraphicsPixmapItem(pixmap){};
    virtual ~Cellule(){};


};

#endif // CELLULE_H
