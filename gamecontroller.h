#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include<QObject>
#include<QTimer>
#include<QGraphicsScene>
#include"bird.h"
#include<QMouseEvent>
#include<QQueue>
#include"mainwindow.h"
#include<QMediaPlayer>
#include<QSoundEffect>
#include"gameoverdialog.h"
class GameOverDialog;
class Wall;
struct BackGround{
    QPointF pos;
    GameController*controller;

    BackGround();
    void paint(QPainter &painter);
    void advance();

};
struct Land{
    QPointF pos;
    Land();

    void paint(QPainter &painter);
    void advance();
};
enum game_mode{NORMAL,DANCING,WEIGHTLESS};
class GameController:public QObject
{
    Q_OBJECT
public:
    GameController(MainWindow* window,QObject*parent=0);
   // void bird_die(Bird* bird);
    void addWall();
    //void deleteWall(Wall* wall);

    void set_mode(game_mode m);
    game_mode get_mode();
public slots:
    void pause();

    void gameOver();
    void advance();
    void paint(QPainter &painter);

protected:
    bool eventFilter(QObject* object,QEvent* event);
private:
    void handleKeyPressed(QKeyEvent* event);
    void handleMouseClick(QMouseEvent* event);

    int score;
    int highest_score;
    Bird* bird;
    QQueue<Wall*> wall_queue;
    MainWindow* window;
    BackGround* bg;
    Land*land;
    int tickCounter;
    QSoundEffect player;
    game_mode mode;
    friend GameOverDialog;


};

#endif // GAMECONTROLLER_H
