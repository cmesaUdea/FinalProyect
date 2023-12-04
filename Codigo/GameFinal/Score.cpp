#include "Score.h"
#include <QFont> //Para dar formato a los textos

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;

    // Texto sin formato
    setPlainText(QString("Score: ") + QString::number(score)); // Score: 0
    setDefaultTextColor(Qt::blue); //Color
    setFont(QFont("times",12)); //Tipo y tamaño
}

void Score::increase(){
    score++;
    setPlainText(QString("Score: ") + QString::number(score)); //Muestra en pantalla el valor de la puntuacion

}

int Score::getScore(){
    return score;
}

void Score::resetScore() {
    score = 0;
    setPlainText(QString("Score: ") + QString::number(score)); // Actualiza el texto mostrado con la puntuación reiniciada
}
