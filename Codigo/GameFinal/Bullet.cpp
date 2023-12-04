#include "Bullet.h"
#include "Enemy.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <Game.h>
#include <Qlist>

extern Game * game; //Objeto global, de tipo puntero

//MiClase::MiClase(QObject *parent) : QObject(parent)
Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) //Constructor y herencia
{
    //dibuja el la bala
    //setRect(0, 0, 10, 50);
    setPixmap(QPixmap(":/images/bala.png"));

    //Conect con el slot de la bala
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this,SLOT(move()));

    timer->start(50);
}

void Bullet::move()
{
    // Eventos para las colisiones
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy) || typeid(*(colliding_items[i])) == typeid(Newenemy)) {
            // Incrementar el puntaje
            game->score->increase();

            // Remueve ambos elementos colisionados
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
        }
    }


    setPos(x(), y()-10);
    if(pos().y()  < 0){
        scene()->removeItem(this);
        delete this;
        //qDebug() <<"Bullet deleted";
    }
}


