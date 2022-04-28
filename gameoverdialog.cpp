#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(GameController* controller,QWidget *parent) :
    QDialog(parent),controller(controller),
    ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);
    ui->bestlabel->setText(QString("%1").arg(controller->highest_score));
    ui->scorelabel->setText(QString("%1").arg(controller->score));
    if(controller->score<controller->highest_score)ui->medalframe->setVisible(false);
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}

void GameOverDialog::on_OkButton_clicked()
{
    close();
}
