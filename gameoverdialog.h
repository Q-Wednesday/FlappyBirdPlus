#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>
#include"gamecontroller.h"
namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverDialog(GameController* controller,QWidget *parent = nullptr);
    ~GameOverDialog();

private slots:
    void on_OkButton_clicked();

private:
    Ui::GameOverDialog *ui;
    GameController* controller;
};

#endif // GAMEOVERDIALOG_H
