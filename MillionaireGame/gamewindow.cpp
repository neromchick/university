#include "gamewindow.h"
#include "startwindow.h"
#include "ui_gamewindow.h"
#include <QPushButton>
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include "styles.h"

gamewindow::gamewindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gamewindow)
{
    ui->setupUi(this);

    answerButtons = { ui->answerBtn1, ui->answerBtn2, ui->answerBtn3, ui->answerBtn4 };
    for (QPushButton* btn : answerButtons)
        connect(btn, &QPushButton::clicked, this, &gamewindow::on_answerBtn_clicked);

    hintButtons = {ui->backToMenuBtn,ui->fiftyFiftyBtn,ui->audienceBtn,ui->callBtn,ui->takeMoneyBtn};
    for(QPushButton* btn : hintButtons)
        connect(btn, &QPushButton::clicked, this, &gamewindow::on_hintBtn_clicked);

    resetStylesAnswerBtn();
    applyStylesHintBtn();

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
        item->setTextAlignment(Qt::AlignCenter); // центрируем текст
        ui->prizeList->addItem(item);
    }

    ui->prizeList->setCurrentRow(14); // уровень 1
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

void gamewindow::startCountdown()
{
    countdown = 15;

    ui->countdownLbl->setText(QString::number(countdown, 'f', 2)); // формат 10.00

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

            QMessageBox::information(this, "Поражение", "Вы проиграли:(");
            on_backToMenuBtn_clicked();
            return;
        }

        ui->countdownLbl->setText(QString::number(countdown, 'f', 2));
    });

    countdownTimer->start();
}

void gamewindow::resetStylesAnswerBtn()
{
    for (auto* btn : answerButtons)
        btn->setStyleSheet(baseAnswerStyle());
}

void gamewindow::applyStylesHintBtn()
{
    for (auto* btn : hintButtons)
        btn->setStyleSheet(hintButtonStyle());
}

void gamewindow::on_hintBtn_clicked()
{

}

void gamewindow::on_answerBtn_clicked()
{
    if (blockClicks) return;
    blockClicks = true;

    if (countdownTimer)
        countdownTimer->stop();

    resetStylesAnswerBtn();

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    QPushButton* rightButton   = ui->answerBtn3; // или динамически correctButton()
    if (!clickedButton || !rightButton) {
        blockClicks = false;
        return;
    }

    bool isCorrect = (clickedButton == rightButton);

    // 1) выбранная кнопка сразу жёлтая
    clickedButton->setStyleSheet(blinkAnswerStyle());

    // 2) через 2 секунды показать результат
    QTimer::singleShot(2000, this, [this, clickedButton, rightButton, isCorrect]() {
        if (isCorrect) {
            clickedButton->setStyleSheet(correctAnswerStyle());
        } else {
            clickedButton->setStyleSheet(wrongAnswerStyle());
            rightButton->setStyleSheet(correctAnswerStyle()); // одновременно зелёный
        }

        // 3) через секунду переход
        QTimer::singleShot(1000, this, [this, isCorrect]() {
            blockClicks = false;
            if (isCorrect)
                proceedToNextLevel();
            else
                on_backToMenuBtn_clicked();
        });
    });
}

void gamewindow::animateBlink(QPushButton* button, int times, int interval,
                              std::function<void()> onFinished)
{
    for (int i = 0; i < times * 2; ++i) {
        QTimer::singleShot(i * interval, this, [button, i]() {
            if (i % 2 == 0) {
                // Жёлтый фон
                button->setStyleSheet(blinkAnswerStyle());
            } else {
                // Возвращаем базовый стиль (тёмный)
                button->setStyleSheet(baseAnswerStyle());
            }
        });
    }

    // Завершающий таймер
    QTimer::singleShot(times * 2 * interval, this, [onFinished]() {
        if (onFinished) onFinished();
    });
}

void gamewindow::proceedToNextLevel()
{
    //QMessageBox::information(this, "Уведомление", QString::number(level));

    QMessageBox::information(this, "Уведомление", prizeLevels[15-level+1-1]);

    resetStylesAnswerBtn();

    loadNextQuestion();
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

void gamewindow::on_backToMenuBtn_clicked()
{
    startwindow *startw = new startwindow();
    startw->show();
    this->hide();
}

void gamewindow::on_takeMoneyBtn_clicked()
{
    if(level > 1 && level < 16)
        emit gameFinished((prizeLevels[15-level+1]).toInt());
    QTimer::singleShot(100, this, [this]() {
        //if (countdownTimer)
            //countdownTimer->stop();
        on_backToMenuBtn_clicked();
    });
    //startwindow *startw = new startwindow();
    //startw->balance = prizeLevels[15-level+1];
    //startw->show();
    //this->hide();
    //if(level > 1 && level < 16)
    //  emit sendBalance(prizeLevels[15-level+1]);
}




