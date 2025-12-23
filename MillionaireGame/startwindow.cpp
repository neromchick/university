#include "startwindow.h"
#include "gamewindow.h"
#include "ui_startwindow.h"
#include "QApplication"
#include "wallet.h"

#include <QMessageBox>

startwindow::startwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::startwindow)
{
    ui->setupUi(this);

    updateBalanceDisplay();
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

void startwindow::onGameFinished(int money)
{
    updateBalanceDisplay();
    this->show();
}

void startwindow::updateBalanceDisplay()
{
    // Берем актуальную сумму из синглтона
    int currentBalance = Wallet::instance().balance();
    ui->balanceLbl->setText(QString::number(currentBalance) + " ₽");
}

void startwindow::updateBalance(int money) {
    updateBalanceDisplay();
}
void startwindow::on_exitBtn_clicked()
{
    QApplication::quit();
}
