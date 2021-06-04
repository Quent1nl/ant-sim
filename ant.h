#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <QWidget>
#include <windows.h>
#include <QObject>
#include <QTimer>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <stack>
#include <cmath>

#include <cellule.h>
#include <food.h>
#include <coordinates.h>




class Ant: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setx /*NOTIFY xChanged*/)
    Q_PROPERTY(qreal y READ y WRITE setY /*NOTIFY yChanged*/)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation /*NOTIFY rotationChanged*/)
public:
    Ant();
    Ant(std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne);
    //Ant(const Ant &ant);
    ~Ant(){};

    Coord getAdjacent();
    void moveAnt();

    std::map<Coord, Cellule*>::iterator cellIt;

    qreal x() const;
    qreal y() const;



    const qreal &rotation() const;
    void setRotation(const qreal &newRotation);
    void rotate(const qreal &end);

private:
    std::map<Coord, Cellule*> mapCellDispo;//map each cells to a coord    
    int nbLigne;    

    Coord newCoord;

    int legPosition;
    void updatePixmap();

    float scaleSize = 0.78;
    qreal m_x;
    qreal m_y;
    QPropertyAnimation * xAnimation;
    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;


    qreal m_rotation;
    std::stack<int> stack; //top = 0 right = 1 bot = 2 left = 3
signals:

public slots :
    void setx(qreal newX);
    void setY(qreal newY);

};

#endif // ANT_H
