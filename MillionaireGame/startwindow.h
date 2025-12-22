#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"

namespace Ui {
class startwindow;
}

class startwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit startwindow(QWidget *parent = nullptr);
    ~startwindow();

private slots:
    void on_startBtn_clicked();
    void on_exitBtn_clicked();
    void updateBalance(int money);

public slots:
    void onGameFinished(int money);

private:
    Ui::startwindow *ui;
    int balance = 0;
    gamewindow *currentGame = nullptr;
};

#endif // STARTWINDOW_H
