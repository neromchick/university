#include "gamewindow.h"
#include "startwindow.h"
#include "ui_gamewindow.h"
#include <QPushButton>
#include <QTimer>
#include <QThread>

gamewindow::gamewindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gamewindow)
{
    ui->setupUi(this);

    connect(ui->answerBtn1, &QPushButton::clicked, this, &gamewindow::on_answerBtn_clicked);
    connect(ui->answerBtn2, &QPushButton::clicked, this, &gamewindow::on_answerBtn_clicked);
    connect(ui->answerBtn3, &QPushButton::clicked, this, &gamewindow::on_answerBtn_clicked);
    connect(ui->answerBtn4, &QPushButton::clicked, this, &gamewindow::on_answerBtn_clicked);
}

gamewindow::~gamewindow()
{
    delete ui;
}



void gamewindow::on_answerBtn_clicked()
{
    if (blockClicks) return;

    resetStylesAnswerBtn();
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    blockClicks = true;

    int blinkCount = 4;
    int blinkInterval = 200;

    // Мигание: чередуем жёлтый и сброс
    for (int i = 0; i < blinkCount; ++i) {
        int onTime = i * 2 * blinkInterval;
        int offTime = onTime + blinkInterval;

        QTimer::singleShot(onTime, this, [this, clickedButton]() {
            clickedButton->setStyleSheet("background-color: yellow;");
        });

        QTimer::singleShot(offTime, this, [this, clickedButton]() {
            clickedButton->setStyleSheet("");
        });
    }

    // Подсветка результата после мигания
    int resultTime = blinkCount * 2 * blinkInterval;
    QTimer::singleShot(resultTime, this, [this, clickedButton]() {
        if (clickedButton == ui->answerBtn3) {
            clickedButton->setStyleSheet("background-color: green;");
        } else {
            clickedButton->setStyleSheet("background-color: red;");
        }
    });

    // Переход к следующему действию через паузу после подсветки
    int transitionTime = resultTime + 1000;
    QTimer::singleShot(transitionTime, this, [this, clickedButton]() {
        blockClicks = false;

        if (clickedButton == ui->answerBtn3) {
            proceedToNextLevel();
        } else {
            on_backToMenuBtn_clicked();
        }
    });
}



void gamewindow::resetStylesAnswerBtn()
{
    ui->answerBtn1->setStyleSheet("");
    ui->answerBtn2->setStyleSheet("");
    ui->answerBtn3->setStyleSheet("");
    ui->answerBtn4->setStyleSheet("");
}


void gamewindow::loadNextQuestion()
{
    level++;
    ui->valueLevelLbl->setText("Вопрос " + QString::number(level) + "/15");
    setEnabled(true);
}

void gamewindow::proceedToNextLevel()
{
    // Сброс стиля у всех кнопок
    resetStylesAnswerBtn();

    // Здесь логика перехода на следующий уровень
    // Например: загрузка нового вопроса
    loadNextQuestion(); // если у тебя есть такая функция
}

void gamewindow::on_backToMenuBtn_clicked()
{
    setEnabled(true);
    startwindow *startw = new startwindow();
    startw->show();
    this->hide();
}

