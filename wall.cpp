#include"wall.h"
#include<QPainter>
#include<QDebug>
#include"constants.h"


Wall::Wall(qreal y,int type,GameController& controller):
    controller(controller){
    pos.setX(800);
     pos.setY(y);
     m_type=type;
}

QRectF Wall::boundingRect() {
    //墙宽20，给过的空间80
    if(m_type){//下方墙
        return QRectF(pos.x()-WIDTH/2,
                      pos.y()+DOOR/2,
                      WIDTH,320);
    }
    else{
        return QRectF(pos.x()-WIDTH/2,pos.y()-DOOR/2-320,WIDTH,320);
    }
}

void Wall::paint(QPainter &painter){
    if(m_type){
        painter.drawImage(boundingRect(),QImage(":/images/pipeu"));
    }
    else{
        painter.drawImage(boundingRect(),QImage(":/images/piped"));
    }
}

void Wall::advance(){
        pos.setX(pos.x()-xspeed);

}
