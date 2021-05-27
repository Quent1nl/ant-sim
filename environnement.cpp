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
    this->resize(coord.x *100 + 230, coord.y*100 + 230);




    //layout de la fenêtre
    this->setLayout(new QVBoxLayout);
    //graphicView qui contient graphic scene
    view = new QGraphicsView(this);
    this->layout()->addWidget(view);
    //graphic Scene, on y insère des widgets
    scene = new QGraphicsScene;
    view->setScene(scene);

    //map each cells to a coord
    int id = 0;
    for (int x=0; x<coord.x*100; x+=100){
        for (int y=0; y<coord.y*100; y+=100){
            this->mapCellule.insert(std::make_pair(Coord(x, y, id++), new Cellule()));
        }
    }

    int i = 0;
    for (const auto &p : this->mapCellule)
    {

        QGraphicsTextItem *textscene = scene->addText(QString::number(i++));
        textscene->setPos(p.first.x, p.first.y);
    }

    //border
    QPixmap Cobble = QPixmap(":/assets/cobblestone.png");
    for (int x=-100; x<=coord.x*100; x+=100){ //horizontal border

        Obstacle* border = new Obstacle(Cobble);
        border->setScale(0.78);
        border->setPos(x,-100);
        scene->addItem(border);

        Obstacle* border2 = new Obstacle(Cobble);
        border2->setScale(0.78);
        border2->setPos(x, coord.y * 100 );
        scene->addItem(border2);
    }
    for (int y=-100; y<coord.y*100; y+=100){ //vertical border

        Obstacle* border = new Obstacle(Cobble);
        border->setScale(0.78);
        border->setPos(-100, y);
        scene->addItem(border);

        Obstacle* border2 = new Obstacle(Cobble);
        border2->setScale(0.78);
        border2->setPos(coord.x*100, y);
        scene->addItem(border2);
    }





    //delete border;

    //this->showMap();

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
                  << ':'
                  << p.second   // string's value
                  << std::endl;
    }
    std::cout<<this->mapCellule.size();

}


