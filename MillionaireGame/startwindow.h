#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>

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

private:
    Ui::startwindow *ui;
};

#endif // STARTWINDOW_H
