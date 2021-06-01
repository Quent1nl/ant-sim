#include "environnement.h"
#include "ui_environnement.h"



environnement::environnement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::environnement)
{
    ui->setupUi(this); 
}

environnement::environnement(Coord coord,QWidget *parent ):
    QWidget(parent),
    ui(new Ui::environnement)
{
    this->coord = coord;
    ui->setupUi(this);
    this->resize(this->coord.x * caseSize + 230, this->coord.y* caseSize + 230);

    //layout de la fenêtre
    this->setLayout(new QVBoxLayout);
    //graphicView qui contient graphic scene
    view = new QGraphicsView(this);
    this->layout()->addWidget(view);

    //graphic Scene, on y insère des widgets
    scene = new QGraphicsScene;
    view->setScene(scene);





    //map each cells to a coord
    QPixmap dirt = QPixmap(":/assets/dirt.png");
//    //ant png
//    QPixmap oldAnt(":/assets/ant.png");
//    QPixmap ant = oldAnt.scaled(QSize(50,50),  Qt::KeepAspectRatio);
//    //change color of the ant
//    auto mask = ant.createMaskFromColor(QColor(0, 0, 0),Qt::MaskOutColor )  ;
//    QPainter p (&ant);
//    p.setPen(QColor(0, 0, 255));
//    p.drawPixmap(ant.rect(), mask, mask.rect());
//    p.end();

    int id = 0;
    for (int x=0; x<this->coord.x* caseSize; x+= caseSize){
        for (int y=0; y<this->coord.y* caseSize; y+= caseSize){
            //QPainter painter(&dirt);
            //painter.drawPixmap(x+50, y+40, ant);//add ant on cell png
            Cellule* cellule = new Cellule(dirt);
            this->mapCellDispo.insert(std::make_pair(Coord(x, y, ++id), cellule));
        }
    }

//    generateAntHill(coord);
//    generateObstacle(coord);//bordure + obstacle
//    generateFood(coord);//food
//    generateFloor();//floor

}


environnement::~environnement()
{
    delete ui;
    delete view;
    delete scene;
}

void environnement::showMap(){
    for (const auto &p : this->mapCellDispo)
    {
        std::cout << "x : " << p.first.x << std::endl // string (key)
                  << "y : " << p.first.y << std::endl
                  << "id : " << p.first.id << std::endl // string (key)
                  << ':'
                  << p.second   // string's value
                  << std::endl;

    }
    std::cout<<this->mapCellDispo.size();

}

void environnement::generateObstacle(){
    //border
    QPixmap oldBedRock = QPixmap(":/assets/bedrock.png");
    QPixmap vBedRock = oldBedRock.scaled(QSize(10,100),  Qt::IgnoreAspectRatio);
    QPixmap hBedRock = oldBedRock.scaled(QSize(100,10),  Qt::IgnoreAspectRatio);
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
    for (int i = 1; i <= std::round(std::sqrt(this->coord.x * this->coord.y)); i++ )//nombre de nourriture max
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

void environnement::generateFood(){
    //food
    QPixmap foodPng = QPixmap(":/assets/food.png");
    for (int i = 1; i <= std::round(std::sqrt(this->coord.x * this->coord.y)); i++ ) //nombre de nourriture max
    {
        Food* food = new Food(foodPng);
        this->cellIt = this->mapCellDispo.begin();
        auto newIt = std::next(this->cellIt, std::rand() % this->mapCellDispo.size() );//select a random cell available
        //std::cout<<"d:"<<newIt->first.id<<std::endl;
        this->mapFood.insert(std::make_pair(newIt->first, food));//insert the new food cell in the food map
        this->mapCellDispo.erase(newIt);//remove the cell from available cells
        food->setScale(imgSize);
        food->setPos(newIt->first.x,newIt->first.y);
        this->scene->addItem(food);
    }
}

void environnement::generateFloor(){
    //add normal floor
    for (const auto &p : this->mapCellDispo)//iterate through all cells still available
    {
        p.second->setScale(imgSize);
        p.second->setPos(p.first.x,p.first.y);
        this->scene->addItem(p.second);
    }
}

void environnement::generateAntHill(){
    //antHill
    QPixmap antHillPng = QPixmap(":/assets/green.png");
    AntHill* antHill = new AntHill(antHillPng);
    this->cellIt = this->mapCellDispo.begin();
    auto newIt = std::next(this->cellIt, std::rand() % this->mapCellDispo.size() );//select a random cell available

    Coord antHillCoord(newIt->first.x, newIt->first.y, newIt->first.id);
    this->mapAntHill.insert(std::make_pair(antHillCoord, antHill));//insert the new antHill cell in the antHill map
    this->mapCellDispo.erase(newIt);//remove the cell from available cells
    antHill->setScale(imgSize);    
    antHill->setPos(antHillCoord.x,antHillCoord.y);
    this->scene->addItem(antHill);

    //create random ants
    QPixmap antPng(":/assets/ant.png");
    Ant *ant = new Ant(antPng, this->mapCellDispo, this->mapFood, this->coord.y);
    ant->setScale(0.78);

    this->mapAnt.insert(std::make_pair(ant,antHill));
}

void environnement::moveAnt(){

    QPixmap antPng(":/assets/ant.png");
    Ant *ant = new Ant(antPng, this->mapCellDispo, this->mapFood, this->coord.y);
    ant->setFlag(QGraphicsItem::ItemIsMovable, true);
    ant->setScale(0.78);
    this->antHillIt = this->mapAntHill.begin();
    auto newIt = std::next(this->antHillIt, std::rand() % this->mapAntHill.size() );//select a antHill  available
    Coord antHillCoord(newIt->first.x, newIt->first.y, newIt->first.id);
    Coord destination = ant->getAdjacent(antHillCoord);

    ant->setPos(destination.x, destination.y);
    ant->setZValue(2);
    this->scene->addItem(ant);
    for (int i = 0; i<30;i++){
        ant->moveAnt();
        Sleep(16);
    }

}


