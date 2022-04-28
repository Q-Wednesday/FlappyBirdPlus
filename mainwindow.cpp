#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include"gamecontroller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),timer(new QTimer(this))
    , ui(new Ui::MainWindow),controller(new GameController(this))
{
    ui->setupUi(this);
    setFixedSize(800,600);
    player.setMedia(QUrl("qrc:/sounds/bgm"));
    player.setVolume(10);
    player.play();
    ui->ResumeBtn->setVisible(false);
    ui->PauseBtn->setVisible(false);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
    delete timer;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    controller->paint(painter);


      //qDebug()<<geometry().width()<<geometry().height();
}


void MainWindow::paintall(){
    update();
}
void MainWindow::on_StartBtn_clicked()
{
    timer->start(1000/33);
    connect(timer,SIGNAL(timeout()),controller,SLOT(advance()));
    connect(timer,SIGNAL(timeout()),this,SLOT(paintall()));
    this->installEventFilter(controller);
    hideall();
}

QPushButton* MainWindow::getStartBtn(){
    return ui->StartBtn;
}
QTimer* MainWindow::getTimer(){
    return timer;
}

QLabel* MainWindow::getScore(){
    return ui->score_label;
}
QLabel*  MainWindow::getHScore(){
    return ui->hscore_label;
}

void MainWindow::on_PauseBtn_clicked()
{
    controller->pause();
    ui->ResumeBtn->setVisible(true);
}

void MainWindow::on_ResumeBtn_clicked()
{
    connect(timer,SIGNAL(timeout()),controller,SLOT(advance()));
    connect(timer,SIGNAL(timeout()),this,SLOT(paintall()));
    this->installEventFilter(controller);
    hideall();
}


void MainWindow::showall(){
    ui->StartBtn->setVisible(true);
    ui->mode1btn->setVisible(true);
    ui->mode_label->setVisible(true);
    ui->mode2btn->setVisible(true);
    ui->PauseBtn->setVisible(false);
}
void MainWindow::hideall(){
    ui->ResumeBtn->setVisible(false);
    ui->mode1btn->setVisible(false);
    ui->mode_label->setVisible(false);
    ui->mode2btn->setVisible(false);
    ui->StartBtn->setVisible(false);
    ui->PauseBtn->setVisible(true);
}
void MainWindow::on_mode1btn_clicked()
{
    if(controller->get_mode()!=DANCING){
    controller->set_mode(DANCING);

    ui->mode_label->setText("LET'S DANCING!");
    }
    else{
        controller->set_mode(NORMAL);
        ui->mode_label->setText("NORMAL MODE");
    }

}

QPushButton* MainWindow::getResumeBtn(){
    return  ui->ResumeBtn;
}

void MainWindow::on_mode2btn_clicked()
{
    if(controller->get_mode()!=WEIGHTLESS){
        controller->set_mode(WEIGHTLESS);
        ui->mode_label->setText("Wightless Now");

    }else{
        controller->set_mode(NORMAL);
        ui->mode_label->setText("NORMAL MODE");
    }
}
