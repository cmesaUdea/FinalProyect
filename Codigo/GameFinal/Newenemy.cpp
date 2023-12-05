#include "Newenemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"
#include <cmath>
#include <QtMath> //Para poder usar grados en el juego

extern Game * game;

//MiClase::MiClase(QObject *parent) : QObject(parent)
Newenemy::Newenemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) //Constructor y herencia
{


    //Creará un entero aleatorio
    int random_number = rand() % 700; //700 porque no quiero que se cree por fuera de la pantall
    setPos(random_number, 0);

    //dibuja el enemigo
    setPixmap(QPixmap(":/images/bomba.png"));



    //Conect con el slot de la bala
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this,SLOT(move()));

    timer->start(50);
}

void Newenemy::move()
{
    //Enemigo moviendose hacia abajo
    setPos(x(), y()+ speed);

    //Cuando los enemigos salgan de la pantalla
    if(pos().y() > 600){

        //Disminuir la vida
        game->health->decrease();
        //Se remueve cada enemigo
        scene()->removeItem(this);
        delete this;

    }
}



void Newenemy::setSpeed(int newSpeed)
{
    speed = newSpeed; // Establece la nueva velocidad
}







