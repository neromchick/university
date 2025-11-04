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

    answerButtons = { ui->answerBtn1, ui->answerBtn2, ui->answerBtn3, ui->answerBtn4 };
    for (QPushButton* btn : answerButtons)
        connect(btn, &QPushButton::clicked, this, &gamewindow::on_answerBtn_clicked);

    startCountdown();
    //ui->prizeList->setCurrentRow(14);
    initPrizeList();
}

gamewindow::~gamewindow()
{
    delete ui;
}

QStringList prizeLevels = {
    "1 000 000", "700 000", "400 000", "200 000", "100 000",
    "50 000", "25 000", "15 000", "10 000", "5 000",
    "2 000", "1 000", "500", "200", "100"
};

void gamewindow::initPrizeList()
{
    ui->prizeList->clear();
    for (const QString& prize : prizeLevels) {
        QListWidgetItem* item = new QListWidgetItem(prize);
        item->setTextAlignment(Qt::AlignCenter); // ← центрируем текст
        ui->prizeList->addItem(item);
    }

    ui->prizeList->setCurrentRow(14); // уровень 1 — внизу
    ui->prizeList->setFixedHeight(15 * 30); // 450 px
    ui->prizeList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->prizeList->setSpacing(0);
    ui->prizeList->setContentsMargins(0, 0, 0, 0);
    int totalHeight = 0;
    for (int i = 0; i < ui->prizeList->count(); ++i) {
        QListWidgetItem* item = ui->prizeList->item(i);
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        totalHeight += 30;
    }
    ui->prizeList->setFixedHeight(totalHeight);
    ui->prizeList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->prizeList->setMinimumHeight(ui->prizeList->sizeHintForRow(0) * ui->prizeList->count());
    ui->prizeList->setMaximumHeight(ui->prizeList->sizeHintForRow(0) * ui->prizeList->count());

    for (int i = 0; i < ui->prizeList->count(); ++i) {
        QListWidgetItem* item = ui->prizeList->item(i);
        item->setSizeHint(QSize(item->sizeHint().width(), 30)); // высота 30 px
    }
}

void gamewindow::on_answerBtn_clicked()
{
    if (blockClicks) return;
    blockClicks = true;

    if (countdownTimer) {
        countdownTimer->stop(); //останавливаем таймер
    }

    resetStylesAnswerBtn();
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());

    animateBlink(clickedButton, 4, 150, [this, clickedButton]() {
        showAnswerResult(clickedButton);
    });
}

void gamewindow::animateBlink(QPushButton* button, int times, int interval, std::function<void()> onFinished)
{
    for (int i = 0; i < times; ++i) {
        int onTime = i * 2 * interval;
        int offTime = onTime + interval;

        QTimer::singleShot(onTime, this, [button]() {
            button->setStyleSheet("background-color: yellow;");
        });

        QTimer::singleShot(offTime, this, [button]() {
            button->setStyleSheet("");
        });
    }

    int totalTime = times * 2 * interval;
    QTimer::singleShot(totalTime, this, onFinished);
}

void gamewindow::showAnswerResult(QPushButton* clickedButton)
{
    bool correct = (clickedButton == ui->answerBtn3);

    if (correct) {
        clickedButton->setStyleSheet("background-color: green;");
    } else {
        clickedButton->setStyleSheet("background-color: red;");
        ui->answerBtn3->setStyleSheet("background-color: green;");
    }

    QTimer::singleShot(1000, this, [this, correct]() {
        blockClicks = false;
        if (correct) {
            proceedToNextLevel();
        } else {
            on_backToMenuBtn_clicked();
        }
    });
}

void gamewindow::startCountdown()
{
    countdown = 15.00;
    ui->countdownLbl->setText(QString::number(countdown, 'f', 2)); // формат: 10.00

    if (countdownTimer) {
        countdownTimer->stop();
        countdownTimer->deleteLater();
    }

    countdownTimer = new QTimer(this);
    countdownTimer->setInterval(10); // каждые 10 мс

    connect(countdownTimer, &QTimer::timeout, this, [this]() {
        countdown -= 0.01;
        if (countdown <= 0.0) {
            countdownTimer->stop();
            ui->countdownLbl->setText("0.00");
            on_backToMenuBtn_clicked(); // или другой переход
            return;
        }

        ui->countdownLbl->setText(QString::number(countdown, 'f', 2));
    });

    countdownTimer->start();
}

void gamewindow::resetStylesAnswerBtn()
{
    for (QPushButton* btn : answerButtons)
        btn->setStyleSheet("");
}

void gamewindow::loadNextQuestion()
{
    level++;
    ui->valueLevelLbl->setText("Вопрос " + QString::number(level) + "/15");
    startCountdown();

    if (level <= 15) {
        ui->prizeList->setCurrentRow(15 - level);
    }
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

