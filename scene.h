#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void startGame();

signals:

};

#endif // SCENE_H
