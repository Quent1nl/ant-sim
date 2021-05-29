#include "ant.h"


Coord Ant::getAdjacent(Coord& coord, std::map<Coord, Cellule*>& Ant, int nbLigne){

    this->cellIt = Ant.find(coord);
    std::cout<< "Coord de la fourmi x: "<<this->cellIt->first.x<< "y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
    Coord co;
    Coord newCoord(0,0,0);

    while (true){
        switch(rand()%4 + 1 ){
        case 1:
            co.id = coord.id - 1;
            this->cellIt = Ant.find(co);
            std::cout<< "case en haut de la fourmi x: "<<this->cellIt->first.x<< "y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            break;

        case 2:
            co.id = coord.id - 1;
            this->cellIt = Ant.find(co);
            std::cout<< "case en haut de la fourmi x: "<<this->cellIt->first.x<< "y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            break;

        case 3:
            co.id = coord.id - nbLigne;
            this->cellIt = Ant.find(co);
            std::cout<< "case a gauche de la fourmi x: "<<this->cellIt->first.x<< "y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            break;

        case 4:
            co.id = coord.id + nbLigne;
            this->cellIt = Ant.find(co);
            std::cout<< "case a droite de la fourmi x: "<<this->cellIt->first.x<< "y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            break;
        }
        if (this->cellIt->first.id)
        {
            newCoord.id = this->cellIt->first.id;
            newCoord.x = this->cellIt->first.x;
            newCoord.y = this->cellIt->first.y;
            return newCoord;
        }
    return newCoord;

    }
}

void Ant::moveAnt(Coord &oldCoord, Coord& newCoord){
    Coord coord(newCoord.x - oldCoord.x, newCoord.y - oldCoord.y, 0);
    for (int i = 0; i < 100 ; i++){

        oldCoord.x += (coord.x / 100);
        oldCoord.y += (coord.y / 100);
        this->setPos(oldCoord.x, oldCoord.y);
    }
}


