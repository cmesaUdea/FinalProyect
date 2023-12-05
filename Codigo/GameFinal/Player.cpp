#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Newenemy.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <Qdebug>


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/disparo.mp3"));

    setPixmap(QPixmap(":/images/Rick.png"));

}

void Player::keyPressEvent(QKeyEvent *event)
{
    //qDebug() <<"Presionanate una tecla";

    if( event-> key() == Qt::Key_Left){
        if(pos().x() > 0)
            setPos(x() - 10, y());
    }

    else     if( event-> key() == Qt::Key_Right){
        if(pos().x() + 100 < 800)
            setPos(x() + 10, y());
    }


    ///Ahora se define la tecla para realizar ataques (espacio)
    else     if( event-> key() == Qt::Key_Space){
        //Crea un bala

        Bullet * bullet = new Bullet ();
        bullet->setPos(x(),y());
        //qDebug() <<"Bullet created";
        scene()->addItem(bullet);

        //Se cree el sonido de la bala
        if(bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }else if(bulletsound->state()==QMediaPlayer::StoppedState){
            bulletsound->play();
        }


    }

}

void Player::spawn()
{
    //crear un enemigo
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);

}

void Player::boom()
{
    //crear un enemigo
    Newenemy * enemy2 = new Newenemy();
    scene()->addItem(enemy2);

}
