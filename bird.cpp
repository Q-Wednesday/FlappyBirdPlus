#include"bird.h"
#include"gamecontroller.h"
#include"constants.h"
Bird::Bird(GameController& controller):
controller(controller)
{
    pos.setX(400);
    pos.setY(300);
    speed=0;
    tickCounter=0;
}

void Bird::paint(QPainter& painter){

      painter.drawImage(QRectF(pos.x()-24,pos.y()-24,48,48),QImage(QString(":/images/bird%1").arg(tickCounter)));

}
QRectF Bird::boundingRect(){
    QRectF bound=QRectF(pos.x()-18,pos.y()-14,37,28);
    return bound;
}

void Bird::advance(){
    tickCounter=(tickCounter+1)%3;
    if(controller.get_mode()==WEIGHTLESS)speed+=low_g;
    else
    speed+=g;

    if(pos.y()>=0){
           pos.setY(pos.y()+speed);
       }
        else{
           speed=2;
           pos.setY(0);
       }
}

void Bird::goUp(){
    if(pos.y()>=0)
    {
    speed=-5;
    pos.setY(pos.y()-20);
    }
}

QPointF Bird::getPos(){
    return pos;
}

void Bird::reset(){
    pos.setX(400);
    pos.setY(300);
    speed=0;
}
