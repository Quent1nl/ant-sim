#include "anthill.h"

//AntHill::AntHill(QPixmap pixmap, std::map<Coord , Cellule*>& mapCellDispo , std::map<Coord, Food*>& mapFood,  int nbLigne ) : QGraphicsPixmapItem(pixmap){
//    this->mapCellDispo = mapCellDispo;
//    this->mapFood = mapFood;
//    this->nbLigne = nbLigne;
//};

void AntHill::deplacement(){
    this->oldCoord.x = 100; this->oldCoord.y = 300 ; this->oldCoord.id = 9;
    this->newCoord = ant->getAdjacent(this->oldCoord, mapCellDispo, nbLigne);
    ant->moveAnt(this->oldCoord, this->newCoord);
    std::cout<<"deplacement"<<std::endl;
}
