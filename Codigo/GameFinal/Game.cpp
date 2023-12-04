#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include "Newenemy.h"
#include <QMediaPlayer>
#include <QImage>
#include <QBrush>
#include <QMessageBox> //Para imprimir mensajes

#include <QCoreApplication>

Game::Game(QWidget *parent){

    int timeEnemy = 2000;
    //int level = 1;

    // create the scene
    scene = new QGraphicsScene(); //Se crea el rectangulo o escena
    scene->setSceneRect(0,0,800,600); // Funcion para redimencionar la escena a mi gusto
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));

    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Anula el scroll en x
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Anula el scroll en y
    setFixedSize(800,600);

    // crea un nuevo jugador
    player = new Player();
    //player->setRect(0,0,100,100); // Cambia la dimensión de objeto creado
    player->setPos(400,450); // Ubica el objeto creado en las coordenada especificadas

    player->setFlag(QGraphicsItem::ItemIsFocusable);//Player será el foco de la pantalla
    player->setFocus();

    scene->addItem(player); //Lanza el objeto creado anteriormente a la escena

    // Crea las clases vidas y puntos
    score = new Score();
    scene->addItem(score);

    //Posiciona las vidas en el juego
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    // Creación de enemigos
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(timeEnemy); //Cada 2 segundo se genera un enemigo

    //Comprobar el nivel de salud
    QTimer * healthCheckTimer = new QTimer();
    QObject::connect(healthCheckTimer, &QTimer::timeout, [this, timer, healthCheckTimer]() {

        if(health->getHealth() == 0 || health->getHealth() <= 0){
            timer->stop();

            // Utiliza QMessageBox para mostrar el mensaje de "Game Over"
            QMessageBox gameOverMessageBox;
            gameOverMessageBox.setText("Game Over, has pérdido, para volver a jugar cierra la ventana del juego");
                gameOverMessageBox.setFont(QFont("Arial", 10)); // Ajusta la fuente según tus preferencias

            // Oculta al jugador
            player->hide();

            // Oculta a los enemigos
            QList<QGraphicsItem*> enemies = scene->items();
            for (QGraphicsItem* item : enemies) {
                if (dynamic_cast<Enemy*>(item)) {
                    item->hide();
                }
            }

            //Musica para anunciar que se perdio
            QMediaPlayer * musicLoser = new QMediaPlayer();
            musicLoser->setMedia(QUrl("qrc:/sounds/loserMusic.mp3"));
            musicLoser->play();

            gameOverMessageBox.exec();
            //music->stop();

        }
    });

    healthCheckTimer->start(1000);  // Comprobar la salud cada segundo

    // Bloque para subir el nivel del juego
    int limitPoint = 3; // Inicializa limitPoint fuera de la lambda

    QTimer *scoreCheckTimer = new QTimer();
    QObject::connect(scoreCheckTimer, &QTimer::timeout, [this, timeEnemy, limitPoint, timer]() mutable {
        // Obtén la puntuación actual del jugador
        int playerScore = score->getScore();

        // Ajusta la frecuencia de generación de enemigos en función de la puntuación
        if (playerScore >= limitPoint) {

            timer->setInterval(timeEnemy);
            limitPoint = limitPoint + 3;

            // Cambia el fondo cuando se alcanza cierta puntuación
            if (playerScore >= 10) { // Cambia 1 a la puntuación específica a la que deseas cambiar el fondo
                setBackgroundBrush(QBrush(QImage(":/images/bg3.jpg")));

                // Elimina el jugador actual
                scene->removeItem(player);
                delete player;

                // Crea un nuevo jugador en otra posición de la pantalla
                player = new Player();
                player->setPos(400, 390); // Cambia la posición según tus necesidades
                player->setFlag(QGraphicsItem::ItemIsFocusable);
                player->setFocus();
                scene->addItem(player);

                // Oculta los enemigos
                QList<QGraphicsItem*> enemies = scene->items();
                for (QGraphicsItem* item : enemies) {
                    if (dynamic_cast<Enemy*>(item)) {
                        item->hide();
                    }
                }

                // Reinicia los contadores de salud y puntuación
                score->resetScore();
                health->resetHealth();

                // Creación de enemigos
                QTimer * timer = new QTimer();
                QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
                timer->start(timeEnemy); //Cada 2 segundo se genera un enemigo

                // Creación de bombas
                QTimer * timer2 = new QTimer();
                QObject::connect(timer2,SIGNAL(timeout()),player,SLOT(boom()));
                timer2->start(timeEnemy); //Cada 2 segundo se genera un enemigo
            }
        }
    });



    QObject::connect(scoreCheckTimer, &QTimer::timeout, [this, timeEnemy, limitPoint, timer, scoreCheckTimer]() mutable {
        // Obtén la puntuación actual del jugador
        int playerScore = score->getScore();

        // Ajusta la frecuencia de generación de enemigos en función de la puntuación
        if (playerScore >= limitPoint) {

            timer->setInterval(timeEnemy);
            limitPoint = limitPoint + 3;

            // Cambia el fondo cuando se alcanza cierta puntuación
            if (playerScore >= 20) { // Cambia 10 a la puntuación específica a la que deseas ganar

                // Detén los timers
                timer->stop();
                scoreCheckTimer->stop();

                // Muestra el mensaje de "Ganaste"
                QMessageBox winnerMessageBox;
                winnerMessageBox.setText("¡Felicidades, eres el ganador!");
                    winnerMessageBox.setFont(QFont("Arial", 10));
                winnerMessageBox.exec();

                // Cierra la aplicación
                QCoreApplication::quit();
            }
        }
    });

    scoreCheckTimer->start(1000); // Comprueba la puntuación cada segundo



    //Se envian los efectos de sonido, sonido ambiente de todo el juego
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/Rikoso.mp3"));
    music->play();

    show();
}
