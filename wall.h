#ifndef WALL_H
#define WALL_H
#include<QObject>
#include"gamecontroller.h"

class Wall:public QObject{
    Q_OBJECT
public:
    Wall(qreal y,int type,GameController &controller);//0代表上方的墙，1代表下方
    QRectF boundingRect();
    void paint(QPainter& painter);
    void advance();



private:
    QPointF pos;
    friend GameController;
    GameController& controller;
    int m_type;
    bool move;
    bool move_mode;
};

#endif // WALL_H
