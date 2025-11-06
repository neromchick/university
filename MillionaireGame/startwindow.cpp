#include "startwindow.h"
#include "gamewindow.h"
#include "ui_startwindow.h"
#include "QApplication"

startwindow::startwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::startwindow)
{
    ui->setupUi(this);
    ui->balanceLbl->setText(balance);
}

startwindow::~startwindow()
{
    delete ui;
}


void startwindow::on_startBtn_clicked()
{
    gamewindow *game = new gamewindow();
    game->show();
    this->hide();
}


void startwindow::on_exitBtn_clicked()
{
    QApplication::quit();
}

void startwindow::recieveBalance(const QString& value)
{
    ui->balanceLbl->setText(value);
}
