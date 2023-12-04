#ifndef HEALTH_H
#define HEALTH_H



#include <QFont>

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    int getHealth();
    void resetHealth(); // Nueva función para reiniciar la salud
private:
    int health;
};

#endif // HEALTH_H
