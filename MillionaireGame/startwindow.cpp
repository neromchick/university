#include "startwindow.h"
#include "gamewindow.h"
#include "ui_startwindow.h"
#include "QApplication"

#include <QMessageBox>

static int balance = 0;

startwindow::startwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::startwindow)
{
    ui->setupUi(this);
    ui->balanceLbl->setText(QString::number(balance));
}

startwindow::~startwindow()
{
    delete ui;
}


void startwindow::on_startBtn_clicked()
{
    gamewindow *game = new gamewindow();

    connect(game, &gamewindow::gameFinished, this, &startwindow::updateBalance);

    game->show();
    this->hide();
}



void startwindow::updateBalance(int money)
{
    balance += money;
    balance += 69;
    ui->balanceLbl->setText(QString::number(balance));

    QMessageBox::information(this, "Уведомление", QString::number(balance));
}

void startwindow::on_exitBtn_clicked()
{
    QApplication::quit();
}
