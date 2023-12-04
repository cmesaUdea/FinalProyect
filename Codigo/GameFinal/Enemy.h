#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Enemy: public QObject,  public QGraphicsPixmapItem{
    Q_OBJECT
public:
    //Se crea el objeto
    Enemy(QGraphicsItem * parent=0);
    void setSpeed(int newSpeed); // Declaración del método
    int speed = 10;

public slots:
    void move();

private:
    qreal velocityY;
};

#endif // ENEMY_H
