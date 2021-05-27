#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "environnement.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //constrain on input
    QIntValidator *validator = new QIntValidator(0, 3000, this);
    ui->inputX->setValidator(validator);
    ui->inputY->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_playButton_clicked()
{
    if (ui->inputX->text().toInt() !=0 ) this->coord.x = ui->inputX->text().toInt();
    if (ui->inputY->text().toInt() !=0 ) this->coord.y = ui->inputY->text().toInt();
    environnement *env = new environnement(this->coord);

    env->show();
    this->close();
}




