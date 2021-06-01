#include "ant.h"


Coord Ant::getAdjacent(const Coord& coord) {


    this->cellIt = this->mapCellDispo.find(coord);
    std::cout<< "Coord de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
    Coord co;

    do {
        switch(rand()%4 + 1 ){
        case 1:
            co.id = coord.id - 1;
            this->cellIt = this->mapCellDispo.find(co);
            std::cout<< "case en haut de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            break;

        case 2:
            co.id = coord.id - 1;
            this->cellIt = this->mapCellDispo.find(co);
            std::cout<< "case en haut de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            break;

        case 3:
            co.id = coord.id - nbLigne;
            this->cellIt = this->mapCellDispo.find(co);
            std::cout<< "case a gauche de la fourmi x: "<<this->cellIt->first.x<< "y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            break;

        case 4:
            co.id = coord.id + nbLigne;
            this->cellIt = this->mapCellDispo.find(co);
            std::cout<< "case a droite de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
            break;
        }
    }

        while(this->cellIt->first.id > nbLigne * nbLigne || this->cellIt->first.id<0);

        std::cout<<this->cellIt->first.id<<std::endl;
        this->newCoord.id = this->cellIt->first.id;
        this->newCoord.x = this->cellIt->first.x;
        this->newCoord.y = this->cellIt->first.y;
        return this->newCoord;


}

void Ant::moveAnt(){

    this->oldCoord.x = this->pos().x(); this->oldCoord.y = this->pos().y(); this->oldCoord.id = (this->nbLigne * (this->oldCoord.x/100)) + 1 + (this->oldCoord.y/100);//id en fonction des coords
    std::cout << "mouvement "<<this->oldCoord.x << " " << this->oldCoord.y << std::endl;
    this->newCoord = getAdjacent(this->oldCoord);
    std::cout << "mouvement "<<this->newCoord.x << " " << this->newCoord.y << std::endl;
    int x = newCoord.x - oldCoord.x;
    int y = newCoord.y - oldCoord.y;
    for (int i = 0; i < 100 ; i++){

        oldCoord.x += (x / 100);
        oldCoord.y += (y / 100);
        this->setPos(oldCoord.x, oldCoord.y);
    }
}


