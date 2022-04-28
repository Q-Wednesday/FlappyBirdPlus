#ifndef BIRD_H
#define BIRD_H
#include<QRectF>
#include<QObject>
#include<QPainter>
class GameController;
class Bird:QObject{
    Q_OBJECT
public:
    Bird(GameController &controller);
    void paint(QPainter& painter);
    QRectF boundingRect();
    void goUp();
    QPointF getPos();
    void advance();
    void reset();
private:
    QPointF pos;
    GameController& controller;
    qreal speed;
    int tickCounter;
    friend GameController;

};

#endif // BIRD_H
