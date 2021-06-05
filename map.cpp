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
    this->setMaximumSize(1500,800);
     //graphicView qui contient graphic scene
    ui->graphicsView->setScene(scene);
}

Map::~Map()
{
    delete ui;
}

void Map::generateCellDispo()
{
    QPixmap dirt = QPixmap(":/assets/dirt.png");
    int id = 0;
    for (int x=0; x<this->coord.x* caseSize; x+= caseSize){
        for (int y=0; y<this->coord.y* caseSize; y+= caseSize){
            //QPainter painter(&dirt);
            //painter.drawPixmap(x+50, y+40, ant);//add ant on cell png
            Cellule* cellule = new Cellule(dirt);
            this->mapCellDispo.insert(std::make_pair(Coord(x, y, ++id), cellule));
        }
    }

}

void Map::generateObstacle()
{
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

void Map::generateIntialFood()
{
    for (int i = 1; i <= std::round(std::sqrt(this->coord.x * this->coord.y)); i++ ) //nombre de nourriture max
    {
        generateFood();
    }

}

void Map::generateFood()
{
    //food

        Food* food = new Food();
        this->cellIt = this->mapCellDispo.begin();
        auto newIt = std::next(this->cellIt, std::rand() % this->mapCellDispo.size() );//select a random cell available
        //std::cout<<"d:"<<newIt->first.id<<std::endl;
        this->mapFood.insert(std::make_pair(newIt->first, food));//insert the new food cell in the food map
        this->mapCellDispo.erase(newIt);//remove the cell from available cells
        food->setScale(imgSize);
        food->setPos(newIt->first.x,newIt->first.y);

        connect(food, &Food::takeFood, [=](){
            this->scene->removeItem(food);
            //nested loop because we need to repopulate the mapCellDispo map, freeing the cell for the next food generation
            for (auto itr = this->mapFood.begin(); itr != this->mapFood.end(); ++itr) {
                if (itr->second == food){
                    for (auto it = this->mapCellDispo.begin(); it != this->mapCellDispo.end(); ++it) {
                        if (it->first == itr->first){
                            this->mapCellDispo.insert(std::make_pair(itr->first,it->second));
                            this->mapFood.erase(itr);
                            goto break_me;
                        }
                    }

                 }
                }
            break_me:
                delete food;
                std::cout<<"food taken"<<std::endl;
        });
        this->scene->addItem(food);


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
    this->cellIt = this->mapCellDispo.begin();
    auto newIt = std::next(this->cellIt, std::rand() % this->mapCellDispo.size() );//select a random cell available

    Coord antHillCoord(newIt->first.x, newIt->first.y, newIt->first.id);
    this->mapAntHill.insert(std::make_pair(antHillCoord, antHill));//insert the new antHill cell in the antHill map
    this->mapCellDispo.erase(newIt);//remove the cell from available cells
    antHill->setScale(imgSize);
    antHill->setPos(antHillCoord.x,antHillCoord.y);
    this->scene->addItem(antHill);
}

void Map::on_playButton_clicked()
{
    if (ui->inputX->text().toFloat() !=0 ) this->coord.x = ui->inputX->text().toFloat();
    if (ui->inputY->text().toFloat() !=0 ) this->coord.y = ui->inputY->text().toFloat();
    //resize
    this->resize((this->coord.x * caseSize) + 70, (this->coord.y* caseSize) + 70);
    //ui->graphicsView->resize(this->coord.x * caseSize +50 , this->coord.y* caseSize+50);
    this->scene->setSceneRect(-10,-10,this->coord.x * caseSize + 20 , this->coord.y* caseSize+20);

    ui->widget->hide();


    generateCellDispo();

    generateObstacle();    
    generateAntHill();
    this->mapMove.insert(this->mapCellDispo.begin(),this->mapCellDispo.end());
    generateIntialFood();
    //generateFood();
    generateFloor();

    Ant * ant = new Ant(this->mapMove, this->coord.y);
    ant->setZValue(3);

    this->scene->addItem(ant);
    ant->moveAnt();
    QTimer * antTimer = new QTimer(this);
    connect(antTimer, &QTimer::timeout,[=](){
           generateFood();
    });
    antTimer->start(5000);

}

