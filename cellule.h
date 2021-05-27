#ifndef CELLULE_H
#define CELLULE_H

#include <QObject>

struct Coord{
    int x=10, y=10, id = 0;
    Coord(){};
    Coord(int x, int y, int id) : x(x), y(y), id(id) {};
};
inline bool operator<(const Coord& coord1, const Coord& coord2) { return  coord1.id < coord2.id; }


class Cellule : public QObject
{
    Q_OBJECT
public:
    explicit Cellule(QObject *parent = nullptr);

    ~Cellule(){};
signals:

};

#endif // CELLULE_H
