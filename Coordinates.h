#ifndef COORDINATES_H
#define COORDINATES_H
struct Coord{
    float x=10, y=10, id = 0;
    Coord(){};
    Coord(float x, float y, float id) : x(x), y(y), id(id) {};
    Coord(const Coord& coord) : x(coord.x), y(coord.y), id(coord.id) {};
    ~Coord(){};
    Coord& operator =(const Coord& coord)
    {
        x = coord.x;
        y = coord.y;
        id = coord.id;
        return *this;
    }

};
inline bool operator<(const Coord& coord1, const Coord& coord2) { return  coord1.id < coord2.id; }
inline bool operator==(const Coord& coord1, const Coord& coord2) { return  coord1.id < coord2.id; }
#endif // COORDINATES_H
