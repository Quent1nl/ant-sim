#include "ant.h"


Coord Ant::getAdjacent(const Coord& coord) {


    this->cellIt = this->mapCellDispo.find(coord); // Find current ant's position
    std::cout<< "Coord de la fourmi x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
    Coord co;

    std::list<int> adjacentCasesIDs = {-1, +1, -nbLigne, +nbLigne}; // List of available cases IDs among up/down/left/right cases
    auto adjacentCasesIDs_front = adjacentCasesIDs.begin(); // Iterator over adjacentCasesIDs
    std::list<Coord> availableAdjacentCases = {}; // List of available cases among up/down/left/right cases
    auto availableAdjacentCases_front = availableAdjacentCases.begin(); // Iterator over adjacentCasesIDs

    for (int i = 0; i < 4; i++ ){
        std::advance(adjacentCasesIDs_front, i); // Go to i-index in list

        std::cout<< "current case id delta : "<<*adjacentCasesIDs_front<<std::endl;

        Coord currentPos;
        currentPos.id = coord.id+*adjacentCasesIDs_front; // Current pos plus delta
        std::cout<< "current case id searched : "<<currentPos.id<<std::endl;
        this->cellIt = this->mapCellDispo.find(currentPos); // Check if pos is available
        std::cout<< "current find case x: "<<this->cellIt->first.x<< " y: "<< this->cellIt->first.y <<" id: " << this->cellIt->first.id <<std::endl;
        if(this->cellIt->first.id <= nbLigne * nbLigne || this->cellIt->first.id < 0) { //Check if pos is not out of range or negative
            availableAdjacentCases.push_back(this->cellIt->first); //Add pos in available adjacent cases
        }
    }

    int randomIndex = rand()%4; // Take rand number between 0 and 4
    std::cout<< "current random id : "<<randomIndex<<std::endl;
    std::advance(availableAdjacentCases, randomIndex); // Go to random pos
    Coord newCoord = *availableAdjacentCases_front; // Set new pos
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


