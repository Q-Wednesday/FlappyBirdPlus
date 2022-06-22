#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFrame>
#include<QTimer>
#include<QPainter>
#include"bird.h"
#include<QTimer>
#include<QLabel>
#include<QMediaPlayer>
#include<QPushButton>
class GameController;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton* getStartBtn();
    QPushButton* getResumeBtn();
    QTimer* getTimer();
    QLabel* getScore();
    QLabel* getHScore();

    void showall();
    void hideall();
private slots:
    //调用绘制
    void paintall();
    //以下是按键对应的事件
    void on_StartBtn_clicked();
    void on_PauseBtn_clicked();
    void on_ResumeBtn_clicked();

private:

    void paintEvent(QPaintEvent*event);


    Ui::MainWindow *ui;
    GameController* controller;
    QTimer* timer;
    QMediaPlayer player;
    friend GameController;
};
#endif // MAINWINDOW_H
