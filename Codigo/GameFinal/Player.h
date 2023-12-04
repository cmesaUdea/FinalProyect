#ifndef MYRECT_CPP
#define MYRECT_CPP

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>

class Player: public QObject, public QGraphicsPixmapItem{ //Se dedifine una clase que hereda de la libreria QGraphicsItem
    Q_OBJECT //Instanciar de una super clase
public:
    bool GameOver = false; //Pendiente
    Player(QGraphicsItem * parent = 0);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void spawn();
    void boom();
private:
    QMediaPlayer * bulletsound;

};

#endif // MYRECT_CPP


