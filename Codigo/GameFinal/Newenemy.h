#ifndef NEWENEMY_H
#define NEWENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QElapsedTimer>

class Newenemy: public QObject,  public QGraphicsPixmapItem{
    Q_OBJECT
public:
    //Se crea el objeto
    Newenemy(QGraphicsItem * parent=0);
    void setSpeed(int newSpeed); // Declaración del método
    int speed = 10;

public slots:
    void move();



};

#endif // NEWENEMY_H
