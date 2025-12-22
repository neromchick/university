#include "startwindow.h"
#include "gamewindow.h"
#include "ui_startwindow.h"
#include "QApplication"

#include <QMessageBox>

startwindow::startwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::startwindow)
{
    ui->setupUi(this);
    ui->balanceLbl->setText(QString::number(balance) + " ₽");
}

startwindow::~startwindow()
{
    delete ui;
}

void startwindow::on_startBtn_clicked()
{
    gamewindow *game = new gamewindow();
    connect(game, &gamewindow::gameFinished, this, &startwindow::onGameFinished);
    game->setAttribute(Qt::WA_DeleteOnClose);
    game->show();
    this->hide();
}
// Этот метод сработает, когда игра пришлет сигнал
void startwindow::onGameFinished(int money)
{
    balance += money;
    ui->balanceLbl->setText(QString::number(balance) + " ₽");
    this->show(); // Показываем главное меню обратно
}

void startwindow::updateBalance(int money)
{
    balance += money;
    ui->balanceLbl->setText(QString::number(balance) + " ₽");
}

void startwindow::on_exitBtn_clicked()
{
    QApplication::quit();
}
