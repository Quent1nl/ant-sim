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
    ui->setupUi(this);
    this->resize(coord.x * caseSize + 230, coord.y* caseSize + 230);

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
    int id = 0;
    for (int x=0; x<coord.x* caseSize; x+= caseSize){
        for (int y=0; y<coord.y* caseSize; y+= caseSize){
            Cellule* cellule = new Cellule(dirt);
            this->mapCellule.insert(std::make_pair(Coord(x, y, ++id), cellule));
        }
    }

    generateObstacle(coord);//bordure + obstacle
    generateFood(coord);//food
    generateFloor();//floor
}


environnement::~environnement()
{
    delete ui;
    delete view;
    delete scene;
}

void environnement::showMap(){
    for (const auto &p : this->mapCellule)
    {
        std::cout << "x : " << p.first.x << std::endl // string (key)
                  << "y : " << p.first.y << std::endl
                  << "id : " << p.first.id << std::endl // string (key)
                  << ':'
                  << p.second   // string's value
                  << std::endl;

    }
    std::cout<<this->mapCellule.size();

}

void environnement::generateObstacle(Coord& coord){
    //border
    QPixmap bedRock = QPixmap(":/assets/bedrock.png");
    for (int x=- caseSize; x<=coord.x* caseSize; x+= caseSize){ //horizontal border

        Obstacle* border = new Obstacle(bedRock);
        border->setScale(imgSize);
        border->setPos(x,- caseSize);
        this->scene->addItem(border);

        Obstacle* border2 = new Obstacle(bedRock);
        border2->setScale(imgSize);
        border2->setPos(x, coord.y *  caseSize );
        this->scene->addItem(border2);
    }
    for (int y=- caseSize; y<coord.y* caseSize; y+= caseSize){ //vertical border

        Obstacle* border = new Obstacle(bedRock);
        border->setScale(imgSize);
        border->setPos(- caseSize, y);
        scene->addItem(border);

        Obstacle* border2 = new Obstacle(bedRock);
        border2->setScale(imgSize);
        border2->setPos(coord.x* caseSize, y);
        scene->addItem(border2);
    }

    //obstacle
    QPixmap cobble = QPixmap(":/assets/cobblestone.png");
    for (int i = 1; i <= std::round(std::sqrt(coord.x * coord.y)); i++ )//nombre de nourriture max
    {
        Obstacle* obstacle = new Obstacle(cobble);
        this->cellIt = this->mapCellule.begin();
        auto newIt = std::next(this->cellIt, std::rand() % this->mapCellule.size() );//select a random cell available
        //std::cout<<"d:"<<newIt->first.id<<std::endl;
        this->mapObstacle.insert(std::make_pair(newIt->first, obstacle));//insert the new food cell in the food map
        this->mapCellule.erase(newIt);
        obstacle->setScale(imgSize);
        obstacle->setPos(newIt->first.x,newIt->first.y);//remove the cell from available cells
        this->scene->addItem(obstacle);
    }
}

void environnement::generateFood(Coord& coord){
    //food
    QPixmap foodPng = QPixmap(":/assets/food.png");
    for (int i = 1; i <= std::round(std::sqrt(coord.x * coord.y)); i++ ) //nombre de nourriture max
    {
        Food* food = new Food(foodPng);
        this->cellIt = this->mapCellule.begin();
        auto newIt = std::next(this->cellIt, std::rand() % this->mapCellule.size() );//select a random cell available
        //std::cout<<"d:"<<newIt->first.id<<std::endl;
        this->mapFood.insert(std::make_pair(newIt->first, food));//insert the new food cell in the food map
        this->mapCellule.erase(newIt);//remove the cell from available cells
        food->setScale(imgSize);
        food->setPos(newIt->first.x,newIt->first.y);
        this->scene->addItem(food);
    }
}

void environnement::generateFloor(){
    //add normal floor
    for (const auto &p : this->mapCellule)//iterate through all cells still available
    {
        p.second->setScale(imgSize);
        p.second->setPos(p.first.x,p.first.y);
        this->scene->addItem(p.second);
    }
}



