#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Coord{
    int x = 1000;
    int y = 1000;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_playButton_clicked();


private:
    Ui::MainWindow *ui;
    Coord coord;
};
#endif // MAINWINDOW_H
