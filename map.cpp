#include "map.h"
#include "ui_map.h"

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    this->scene = new Scene(this);
    //layout de la fenêtre
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(ui->graphicsView);
    this->setMaximumSize(1300,700);
     //graphicView qui contient graphic scene
    ui->graphicsView->setScene(scene);
}

Map::~Map()
{
    delete ui;
}

void Map::on_playButton_clicked()
{
    //get inputs
    if (ui->inputX->text().toFloat() !=0 ) this->coord.x = ui->inputX->text().toFloat();
    if (ui->inputY->text().toFloat() !=0 ) this->coord.y = ui->inputY->text().toFloat();
    //resize
    this->resize((this->coord.x * caseSize) + 70, (this->coord.y* caseSize) + 70);
    //ui->graphicsView->resize(this->coord.x * caseSize +50 , this->coord.y* caseSize+50);
    this->scene->setSceneRect(-10,-10,this->coord.x * caseSize + 20 , this->coord.y* caseSize+20);

    ui->widget->hide();

    int foodRate = ui->inputFood->currentIndex();
    int obstacleRate = ui->inputObstacle->currentIndex();
    //std::cout<<foodRate<<std::endl;

    //put the cells in a maps
    this->mapCellDispo = generateCellDispo(0,0,this->coord.x* caseSize, this->coord.y* caseSize, caseSize);
    //generate obtacles
    generateObstacle(obstacleRate);
    this->mapMove.insert(this->mapCellDispo.begin(),this->mapCellDispo.end());//map will store free cells to move to
    //generate anthill
    generateAntHill();
    //generate floor
    generateFloor();

    //spawn food
    QTimer * antTimer = new QTimer(this);
    connect(antTimer, &QTimer::timeout,[=](){
           generateFood();
    });
    antTimer->start(1500 / ((foodRate + 1)*std::sqrt(std::round(this->coord.x * this->coord.y)/100)));
}


std::map<Coord, Cellule*> Map::generateCellDispo(int xStart, int yStart, int xEnd, int yEnd, int newCaseSize)
{
    std::map<Coord, Cellule*> tempMap;
    QPixmap dirt = QPixmap(":/assets/dirt.png");
    int id = 1;
    for (int x= xStart; x< xEnd; x+= newCaseSize){
        for (int y= yStart; y< yEnd; y+= newCaseSize){
            Cellule* cellule = new Cellule(dirt);
            tempMap.insert(std::make_pair(Coord(x, y, id++), cellule));
        }
    }
    return tempMap;
}

void Map::generateObstacle(int obstacleRate)
{
    //border
    QPixmap oldBedRock = QPixmap(":/assets/bedrock.png");
    QPixmap vBedRock = oldBedRock.scaled(QSize(10,caseSize),  Qt::IgnoreAspectRatio);
    QPixmap hBedRock = oldBedRock.scaled(QSize(caseSize,10),  Qt::IgnoreAspectRatio);
    for (int x= 0; x<this->coord.x* caseSize; x+= caseSize){ //horizontal border

        Obstacle* border = new Obstacle(hBedRock);
        //border->setScale(imgSize);
        border->setPos(x,- 10);
        this->scene->addItem(border);

        Obstacle* border2 = new Obstacle(hBedRock);
        //border2->setScale(imgSize);
        border2->setPos(x, this->coord.y *  caseSize );
        this->scene->addItem(border2);
    }
    for (int y= 0; y<this->coord.y* caseSize; y+= caseSize){ //vertical border

        Obstacle* border = new Obstacle(vBedRock);
        //border->setScale(imgSize);
        border->setPos(-10, y);
        scene->addItem(border);

        Obstacle* border2 = new Obstacle(vBedRock);
        //border2->setScale(imgSize);
        border2->setPos(this->coord.x* caseSize, y);
        scene->addItem(border2);
    }

    //obstacle
    QPixmap cobble = QPixmap(":/assets/cobblestone.png");
    for (int i = 1; i <= std::round(std::sqrt(this->coord.x * this->coord.y)*(obstacleRate+1)); i++ )//nombre de nourriture max
    {
        Obstacle* obstacle = new Obstacle(cobble);
        this->cellIt = this->mapCellDispo.begin();
        auto newIt = std::next(this->cellIt, std::rand() % this->mapCellDispo.size() );//select a random cell available
        //std::cout<<"d:"<<newIt->first.id<<std::endl;
        this->mapObstacle.insert(std::make_pair(newIt->first, obstacle));//insert the new food cell in the food map
        this->mapCellDispo.erase(newIt);
        obstacle->setScale(imgSize);
        obstacle->setPos(newIt->first.x,newIt->first.y);//remove the cell from available cells
        this->scene->addItem(obstacle);
    }
}

void Map::generateIntialFood(int foodRate)
{
    for (int i = 1; i <= std::round((this->coord.x * this->coord.y)/10) * (foodRate+1); i++ ) //nombre de nourriture max
    {
        generateFood();
    }
}

void Map::generateFood()
{
    //food
    if (this->mapCellDispo.size()!=0){
        Food* food = new Food();
        this->cellIt = this->mapCellDispo.begin();
        auto newIt = std::next(this->cellIt, std::rand() % this->mapCellDispo.size() );//select a random cell available
        //std::cout<<"d:"<<newIt->first.id<<std::endl;
        this->mapFood.insert(std::make_pair(newIt->first, food));//insert the new food cell in the food map
        this->mapCellDispo.erase(newIt);//remove the cell from available cells
        food->setScale(imgSize);
        food->setPos(newIt->first.x,newIt->first.y);
        this->scene->addItem(food);
        //when food is taken are vanish
        connect(food, &Food::takeFood, [=](){
            //this->scene->removeItem(food);
            //nested loop because we need to repopulate the mapCellDispo map, freeing the cell for the next food generation
            for (auto itr = this->mapFood.begin(); itr != this->mapFood.end(); ++itr) {
                if (itr->second == food){
                    for (auto it = this->mapMove.begin(); it != this->mapMove.end(); ++it) {
                        if (it->first.id == itr->first.id){
                            //std::cout<<"delete food"<<std::endl;
                            this->mapCellDispo.insert(std::make_pair(itr->first,it->second));
                            this->mapFood.erase(itr);
                            goto break_me;
                        }
                    }
                }
            }
        break_me:;
            //                std::cout<<"food taken"<<std::endl;
        });
    }
}

void Map::generateFloor()
{
    //add normal floor
    for (const auto &p : this->mapMove)//iterate through all cells still available
    {
        p.second->setScale(imgSize);
        p.second->setPos(p.first.x,p.first.y);
        this->scene->addItem(p.second);
    }
}

void Map::generateAntHill()
{
    AntHill* antHill = new AntHill();
    antHill->setZValue(2);

    //select a random cell available
    this->cellIt = this->mapCellDispo.begin();
    auto newIt = std::next(this->cellIt, std::rand() % this->mapCellDispo.size() );

    this->antHillCoord.x = newIt->first.x; this->antHillCoord.y = newIt->first.y ; this->antHillCoord.id = newIt->first.id;
    this->mapAntHill.insert(std::make_pair(this->antHillCoord, antHill));//insert the new antHill cell in the antHill map
    this->mapCellDispo.erase(newIt);//remove the cell from available cells
    antHill->setScale(imgSize);
    antHill->setPos(this->antHillCoord.x,this->antHillCoord.y);
    this->scene->addItem(antHill);    

    //cell dispo in anthill for queen movements
    this->mapCellInAnthill = generateCellDispo(this->antHillCoord.x, this->antHillCoord.y,this->antHillCoord.x+caseSize,this->antHillCoord.y+caseSize,caseSize/10);

    int pheromoneRate = ui->inputEvaporation->currentIndex();
    //create queen with mapCellInAnthill
    Queen * queen = new Queen(":/assets/queen.png",this->mapCellInAnthill, 10,this->antHillCoord, true, QColor(Qt::red));
    queen->setZValue(3);
    this->scene->addItem(queen);
    queen->moveAnt();

    //when queen generate Egg
    connect(queen, &Queen::generateEgg, [=](){
        if (antHill->getLifeAnthill()>=30 && this->mapAnt.size()<15){ //if there is food or less than 15 warriors
            //create egg at the queen coords;
            eggCoord = queen->getNewCoord();
            Egg * egg = new Egg(":/assets/egg.png", this->mapCellInAnthill, 10, eggCoord , true, QColor(Qt::red));
            //consume food and update the botlife
            antHill->setLifeAnthill(-30);
            antHill->updateBotLife();
            egg->setZValue(2);
            this->scene->addItem(egg);
            connect(egg, &Egg::generateLarva, [=](){
                //create larva
                Larva * larva = new Larva(":/assets/larva.png", this->mapCellInAnthill, 10, eggCoord , true, QColor(Qt::red));
                larva->setZValue(2);
                this->scene->addItem(larva);
                connect(larva, &Larva::generateAnt, [=](){
                    //create warrior at the anthill coords
                    Warrior * warrior = new Warrior(":/assets/ant.png", this->mapMove, this->coord.y,antHillCoord, QColor(Qt::red), pheromoneRate);
                    warrior->setZValue(3);
                    //change color of the ant
                    this->scene->addItem(warrior);
                    warrior->moveAnt();

//                    //map each warrior to its anthill
                    this->mapAnt.insert(std::make_pair(warrior,antHill));
                    connect(warrior, &Warrior::warriorDead, [=](){
                        auto it = this->mapAnt.find(warrior);
                        //map each warrior to its anthill
                        this->mapAnt.erase(it);
                    });
                    connect(warrior, &Warrior::updateFood, [=](){
                        antHill->updateFood();
                    });
                });
            });
        }
    });

    QTimer * antTimer = new QTimer(this);
    connect(antTimer, &QTimer::timeout,[=](){
        if (this->mapAnt.size()){
            float lifeMoyenne = 0;
            for (const auto &p : this->mapAnt)
            {
                lifeMoyenne += p.first->getLife();
                //std::cout<<"moyenne life"<<lifeMoyenne<<std::endl;
            }
            lifeMoyenne = lifeMoyenne / (this->mapAnt.size()*20);
            //std::cout<<"moyenne life"<<lifeMoyenne<<std::endl;
            antHill->updateLife(lifeMoyenne);
        }
    });
    antTimer->start(800);


}





