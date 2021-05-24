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

    //layout de la fenêtre
    this->setLayout(new QVBoxLayout);
    //graphicView qui contient graphic scene
    view = new QGraphicsView(this);
    this->layout()->addWidget(view);
    //graphic Scene, on y insère des widgets
    scene = new QGraphicsScene;
    view->setScene(scene);

    // Add the vertical lines first, paint them red
    for (int x=0; x<=coord.x; x+=50)
        scene->addLine(x,0,x,coord.x, QPen(Qt::black));

    // Now add the horizontal lines, paint them green
    for (int y=0; y<=coord.y; y+=50)
        scene->addLine(0,y,coord.y,y, QPen(Qt::black));



}


environnement::~environnement()
{
    delete ui;
}
