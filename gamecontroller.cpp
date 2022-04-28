#include"gamecontroller.h"
#include<QDebug>
#include<QEvent>
#include<QKeyEvent>
#include"wall.h"
#include"constants.h"
#include<QtMath>

//检测碰撞，考虑单独放一个文件吧
bool Check_collision(QRectF birdrect,QRectF wallrect,bool walltype){
    if(walltype){
            if(!(birdrect.x()>wallrect.x()+wallrect.width() ||birdrect.x()+birdrect.width()<wallrect.x())){
                if(birdrect.y()+birdrect.height()>wallrect.y()){
                    return true;
                }
            }
        }
        else{
            if(!(birdrect.x()>wallrect.x()+wallrect.width() ||birdrect.x()+birdrect.width()<wallrect.x())){
                if(birdrect.y()<wallrect.y()+wallrect.height()){
                    return true;
                }
            }
        }
    return false;
}

BackGround::BackGround(){
    pos.setX(0);
    pos.setY(0);


}

Land::Land(){
    pos.setX(0);
    pos.setY(0);

}
void Land::advance(){
    pos.setX(pos.x()-xspeed);
    if(pos.x()<-336){
        pos.setX(0);

    }
}
void Land::paint(QPainter& painter){

    for(int i=0;i<4;i++){
          painter.drawImage(pos.x()+336*i,488,QImage(":/images/land"));
    }
}
void BackGround::advance(){
    pos.setX(pos.x()-xspeed);
    if(pos.x()<-288){
        pos.setX(0);

    }
}
void BackGround::paint(QPainter &painter){



    for(int i=0;i<4;i++){

        if(controller->get_mode()==WEIGHTLESS)
            painter.drawImage(pos.x()+288*i,pos.y(),QImage(":/images/space"));
        else
            painter.drawImage(pos.x()+288*i,pos.y(),QImage(":/images/bg"));

    }
}

GameController::GameController(MainWindow* window,QObject*parent):
    QObject(parent),window(window),tickCounter(0)
{
    bird=new Bird(*this);
    bg=new BackGround;
    bg->controller=this;
    land=new Land;


    score=0;
    highest_score=0;
    player.setSource(QUrl("qrc:/sounds/effect"));
    mode=NORMAL;
}

void GameController::advance(){
    if(!tickCounter){
        addWall();
    }


    tickCounter=(tickCounter+1)%T;
    bird->advance();
    bg->advance();
    land->advance();
    //qDebug()<<wall_queue.size();
    if(!wall_queue.empty()&&wall_queue.head()->pos.x()<0){
        delete wall_queue.head();
        wall_queue.dequeue();}

    for(auto wall:wall_queue){
        wall->advance();
        //qDebug()<<wall->pos.x()<<bird->pos.x();
        if(wall->pos.x()==398&&wall->m_type){
            score++;



            window->getScore()->setText(QString("%1").arg(score));

            if(score>highest_score)highest_score=score;
            window->getHScore()->setText(QString("%1").arg(highest_score));
        }
        if(Check_collision(bird->boundingRect(),wall->boundingRect(),wall->m_type)){
            gameOver();
        }

    }

    if(bird->pos.y()>500)gameOver();

    //qDebug()<<"controller advance";
}
void GameController::gameOver(){
    pause();

    QQueue<Wall*>::iterator itr=wall_queue.begin();
    window->getScore()->setText(QString("0"));

    while(!wall_queue.empty()){
        delete wall_queue.head();
        wall_queue.dequeue();
    }

    //qDebug()<<wall_queue.size();
    bird->reset();
    window->showall();

    GameOverDialog* dialog=new GameOverDialog(this);
    dialog->exec();score=0;


}
void GameController::pause(){
     disconnect(window->getTimer(),SIGNAL(timeout()),this,SLOT(advance()));
     window->removeEventFilter(this);
}

bool GameController::eventFilter(QObject *object, QEvent *event){

    if(event->type()==QEvent::KeyPress){

        handleKeyPressed((QKeyEvent*)event);
        return true;

    }
    else if(event->type()==QEvent::MouseButtonPress||event->type()==QEvent::MouseButtonDblClick){

        handleMouseClick((QMouseEvent*)event);
    }
    else{
        return QObject::eventFilter(object,event);
    }
}

void GameController::handleMouseClick(QMouseEvent *event){
    player.play();
    bird->goUp();
}
void GameController::handleKeyPressed(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_W:qDebug()<<"up";
        bird->goUp();break;
    case Qt::Key_Escape:
        pause();

        window->getResumeBtn()->setVisible(true);
    }
}

void GameController::paint(QPainter&painter){
    bg->paint(painter);

    bird->paint(painter);
    for(auto wall:wall_queue){
        wall->paint(painter);
    }
    land->paint(painter);

}

void GameController::addWall(){
    qreal wally=rand()%270+100;
    Wall* wall1=new Wall(wally,1,*this);
    Wall* wall2=new Wall(wally,0,*this);
    wall_queue.push_back(wall1);
    wall_queue.push_back(wall2);
    if(mode==DANCING){wall1->move=true;wall2->move=true;}
}

void GameController::set_mode(game_mode m){
    mode=m;
}

game_mode GameController::get_mode(){
    return mode;
}
