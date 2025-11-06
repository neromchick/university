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

    resetStylesAnswerBtn();

    connect(this, &gamewindow::sendBalance,new startwindow, &startwindow::recieveBalance);

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

    if (countdownTimer)
        countdownTimer->stop();

    resetStylesAnswerBtn();
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    bool correct = (clickedButton == ui->answerBtn3);

    QString finalStyle = correct
                             ? correctAnswerStyle()
                             : wrongAnswerStyle();

    animateBlink(clickedButton, 4, 150, finalStyle, [this, correct, clickedButton]() {
        if (!correct)
            ui->answerBtn3->setStyleSheet(correctAnswerStyle());

        QTimer::singleShot(1000, this, [this, correct]() {
            blockClicks = false;
            correct ? proceedToNextLevel() : on_backToMenuBtn_clicked();
        });
    });
}



void gamewindow::animateBlink(QPushButton* button, int times, int interval,
                              const QString& finalStyle,
                              std::function<void()> onFinished)
{
    for (int i = 0; i < times * 2; ++i) {
        QTimer::singleShot(i * interval, this, [this, button, i, finalStyle]() {
            button->setStyleSheet(i % 2 == 0
                                      ? blinkAnswerStyle()
                                      : finalStyle);
        });
    }

    QTimer::singleShot(times * 2 * interval, this, onFinished);
}


void gamewindow::resetStylesAnswerBtn()
{
    for (auto* btn : answerButtons)
        btn->setStyleSheet(baseAnswerStyle());
}


void gamewindow::proceedToNextLevel()
{
    // Сброс стиля у всех кнопок
    resetStylesAnswerBtn();

    // Здесь логика перехода на следующий уровень
    // Например: загрузка нового вопроса
    loadNextQuestion(); // если у тебя есть такая функция
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

void gamewindow::on_backToMenuBtn_clicked()
{
    startwindow *startw = new startwindow();
    startw->show();
    this->hide();
}

void gamewindow::on_takeMoneyBtn_clicked()
{
    startwindow *startw = new startwindow();
    startw->balance = prizeLevels[15-level+1];
    startw->show();
    this->hide();
    //if(level > 1 && level < 16)
      //  emit sendBalance(prizeLevels[15-level+1]);
}

QString gamewindow::baseAnswerStyle() const
{
    return R"(
        QPushButton {
            background-color: #1e1e1e;
            color: white;
            font: bold 16px "Segoe UI";
            border: 2px solid #444;
            border-radius: 8px;
            padding: 10px;
            text-align: center;
        }
        QPushButton:hover {
            background-color: #2e2e2e;
            border-color: #888;
        }
        QPushButton:pressed {
            background-color: #0078d7;
            color: white;
            border-color: #005bb5;
        }
    )";
}
QString gamewindow::correctAnswerStyle() const {
    return baseAnswerStyle() + " QPushButton { background-color: green; color: white; }";
}
QString gamewindow::wrongAnswerStyle() const {
    return baseAnswerStyle() + " QPushButton { background-color: red; color: white; }";
}
QString gamewindow::blinkAnswerStyle() const {
    return baseAnswerStyle() + " QPushButton { background-color: yellow; color: black; }";
}
QString gamewindow::answerStyle(const QString& bgColor, const QString& textColor) const {
    return QString(R"(
        QPushButton {
            background-color: %1;
            color: %2;
            font: bold 16px "Segoe UI";
            border: 2px solid #444;
            border-radius: 8px;
            padding: 10px;
            text-align: center;
        }
        QPushButton:hover {
            background-color: #2e2e2e;
            border-color: #888;
        }
        QPushButton:pressed {
            background-color: #0078d7;
            color: white;
            border-color: #005bb5;
        }
    )").arg(bgColor, textColor);
}



