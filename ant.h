#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <QWidget>
#include <windows.h>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QtWidgets>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

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
    Ant(){};
    Ant(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, QColor color);
    Ant(QString antPng, std::map<Coord, Cellule*>& _mapCellDispo, int _nbLigne, Coord &anthillPos, bool isAnthill, QColor color);
    //Ant(const Ant &ant);
    ~Ant(){};

    virtual void moveAnt();

    //position x y de la fourmie
    qreal x() const;
    qreal y() const;

    //get the new coord position
    const Coord &getNewCoord() const;

protected:
    //movement
    Coord getAdjacent();
    Coord newCoord;
    std::map<Coord, Cellule*>::iterator cellIt;//iterateur

    //rotate
    const qreal &rotation() const;
    void setRotation(const qreal &newRotation);
    void rotate(const qreal &end, int duration);

    //animation
    qreal m_x;
    qreal m_y;
    QParallelAnimationGroup * group;//animation de groupe
    QPropertyAnimation * xAnimation;//animation pour le déplacement x
    QPropertyAnimation * yAnimation;//animation pour le déplacement y
    QPropertyAnimation * rotationAnimation;//animation de rotation

    virtual void setAnimationGroup();

    //set pixmaps
    void setAntP(const QPixmap &newAntP, QColor color);
    void setAntP2(const QPixmap &newAntP2, QColor color);

private:
    std::map<Coord, Cellule*> mapCellDispo;//map each cells to a coord

    QString antPng;
    QString antPng2;
    QPixmap antP;
    QPixmap antP2;

    int legPosition;
    void updatePixmap();

    int nbLigne;
    int caseSize= 50 ;

    int idAnthill = 0;
    bool isAnthill = false;

    float scaleSize = 0.4;

    int lastDirection = 0;
    qreal m_rotation;

signals:

public slots :
    virtual void setx(qreal newX);
    virtual void setY(qreal newY);
};

#endif // ANT_H
