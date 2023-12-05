#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> 
#include "Game.h"
#include <cmath>

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) //Constructor y herencia
{
    //Creará un entero aleatorio
    int random_number = rand() % 700; //700 porque no quiero que se cree por fuera de la pantall
    setPos(random_number, 0);

    //dibuja el enemigo
    setPixmap(QPixmap(":/images/alien.png"));

    //Conect con el slot de la bala
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this,SLOT(move()));

    timer->start(50);
}


void Enemy::move()
{
    qreal gravity = 0.2; // Gravedad
    qreal initialVelocity = 0.0; // Velocidad inicial en el eje Y

    // Actualiza la velocidad en el eje Y con la gravedad
    velocityY += gravity;

    // Actualiza la posición en el eje Y según la velocidad
    setPos(x(), y() + velocityY);

    if(pos().y() > 400){

        //Disminuir la vida
        game->health->decrease();
        //Se remueve cada enemigo
        scene()->removeItem(this);
        delete this;

    }
}

void Enemy::setSpeed(int newSpeed)
{
    speed = newSpeed; // Establece la nueva velocidad
}







