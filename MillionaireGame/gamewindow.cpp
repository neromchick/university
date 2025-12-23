#include "gamewindow.h"
#include "startwindow.h"
#include "ui_gamewindow.h"
#include <QPushButton>
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include <QTime>  // Добавьте эту строку
#include <QFile>  // Для работы с файлами
#include <QJsonDocument>  // Для JSON
#include <QJsonArray>     // Для JSON
#include <QJsonObject>    // Для JSON
#include <random>         // Для C++11 random
#include <algorithm>      // Для shuffle
#include "styles.h"
#include "wallet.h"

gamewindow::gamewindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gamewindow)
    , countdownTimer(nullptr)
    , level(1)
    , currentQuestionIndex(0)
    , correctAnswerIndex(-1)
    , blockClicks(false)
    , fiftyFiftyUsed(false)
    , audienceUsed(false)
    , callUsed(false)
{
    ui->setupUi(this);

    // 1. Инициализация движка и менеджера
    qManager = new QuestionManager();
    engine = new GameEngine(this);

    // 2. Настройка кнопок (интерфейс)
    answerButtons = { ui->answerBtn1, ui->answerBtn2, ui->answerBtn3, ui->answerBtn4 };
    for (QPushButton* btn : answerButtons)
        connect(btn, &QPushButton::clicked, this, &gamewindow::on_answerBtn_clicked);

    hintButtons = {ui->backToMenuBtn, ui->fiftyFiftyBtn, ui->audienceBtn,
                   ui->callBtn, ui->takeMoneyBtn};
    for(QPushButton* btn : hintButtons)
        connect(btn, &QPushButton::clicked, this, &gamewindow::on_hintBtn_clicked);

    // 3. Таблица призов
    prizeLevels = {
        "1 000 000", "700 000", "400 000", "200 000", "100 000",
        "50 000", "25 000", "15 000", "10 000", "5 000",
        "2 000", "1 000", "500", "200", "100"
    };

    // 4. Соединяем сигналы ООП-движка с методами окна
    connect(engine, &GameEngine::levelPassed, this, &gamewindow::updateUI);
    connect(engine, &GameEngine::gameWon, this, [this](int prize){
        Wallet::instance().addMoney(prize);
        QMessageBox::information(this, "ПОБЕДА!", "Вы выиграли " + QString::number(prize) + " рублей!");
        this->close();
    });

    // 5. Запуск игры (используем менеджер вопросов)
    if (qManager->loadQuestions("questions.json")) {
        // Загружаем вопросы в движок
        engine->startNewGame(qManager->getRandomQuestions(15));
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить вопросы из JSON!");
    }

    // 6. Визуальная настройка
    resetStylesAnswerBtn();
    applyStylesHintBtn();
    initPrizeList();
}


gamewindow::~gamewindow()
{
    delete ui;
}

void gamewindow::updateUI() {
    // 1. Сбрасываем флаги и стили
    blockClicks = false;
    resetStylesAnswerBtn(); // Твой метод, который ставит baseAnswerStyle()

    // 2. Получаем данные нового вопроса из движка
    Question q = engine->currentQuestion();
    correctAnswerIndex = q.correctIndex; // Синхронизируем индекс для подсказок

    // 3. Заполняем интерфейс
    ui->questionLbl->setText(q.text);
    for(int i = 0; i < 4; i++) {
        answerButtons[i]->setText(q.answers[i]);
        answerButtons[i]->setEnabled(true);
        answerButtons[i]->setVisible(true);
    }

    // 4. Обновляем уровень и призы
    int currentLevel = engine->currentLevel();
    ui->valueLevelLbl->setText(QString("Вопрос %1/15").arg(currentLevel));

    if (ui->prizeList->count() > (15 - currentLevel)) {
        ui->prizeList->setCurrentRow(15 - currentLevel);
    }

    // 5. Перезапуск таймера
    startCountdown();
}

void gamewindow::initPrizeList()
{
    qDebug() << "=== initPrizeList() START ===";

    // Делаем виджет видимым
    ui->prizeList->setVisible(true);
    ui->prizeList->show();

    ui->prizeList->clear();

    // Проверяем prizeLevels
    qDebug() << "prizeLevels size:" << prizeLevels.size();
    qDebug() << "prizeLevels:" << prizeLevels;

    if (prizeLevels.isEmpty()) {
        qDebug() << "ERROR: prizeLevels is empty!";
        return;
    }

    // Простой стиль для теста
    ui->prizeList->setStyleSheet(R"(
        QListWidget {
            background-color: #1e1e1e;
            color: white;
            font: bold 14px "Segoe UI";
            border: 2px solid #444;
            border-radius: 8px;
        }
        QListWidget::item {
            padding: 5px;
            text-align: center;
        }
        QListWidget::item:selected {
            background-color: #FFD700;
            color: black;
        }
    )");

    // Заполняем список
    for (const QString& prize : prizeLevels) {
        QListWidgetItem* item = new QListWidgetItem(prize);
        item->setTextAlignment(Qt::AlignCenter);
        item->setSizeHint(QSize(120, 30)); // Явный размер
        ui->prizeList->addItem(item);
        qDebug() << "Added:" << prize;
    }

    // Проверяем, что элементы добавились
    qDebug() << "After adding - item count:" << ui->prizeList->count();

    // Устанавливаем текущий ряд
    if (ui->prizeList->count() > 0) {
        ui->prizeList->setCurrentRow(14); // уровень 1
        qDebug() << "Current row set to 14";
    }

    // Фиксированные размеры
    ui->prizeList->setFixedSize(131, 460); // Как в геометрии из лога

    // Обновляем отображение
    ui->prizeList->update();
    ui->prizeList->repaint();

    qDebug() << "prizeList visible after init:" << ui->prizeList->isVisible();
    qDebug() << "=== initPrizeList() END ===";
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

            QMessageBox::information(this, "Уведомление", "Вы проиграли по истечению времени:(");
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

void gamewindow::   on_hintBtn_clicked()
{

}

void gamewindow::on_answerBtn_clicked()
{
    if (blockClicks) return;

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    blockClicks = true;
    if (countdownTimer) countdownTimer->stop();

    int clickedIndex = answerButtons.indexOf(clickedButton);

    // 1 ЭТАП: Желтый (на 2 секунды)
    clickedButton->setStyleSheet(blinkAnswerStyle());

    QTimer::singleShot(2000, this, [this, clickedButton, clickedIndex]() {
        // Проверяем через движок
        bool isCorrect = engine->checkAnswer(clickedIndex);

        // 2 ЭТАП: Показываем результат (на 1 секунду)
        if (isCorrect) {
            clickedButton->setStyleSheet(correctAnswerStyle());
        } else {
            clickedButton->setStyleSheet(wrongAnswerStyle());
            // Подсвечиваем правильный (берем из текущего вопроса движка)
            int correctIdx = engine->currentQuestion().correctIndex;
            if (correctIdx >= 0) answerButtons[correctIdx]->setStyleSheet(correctAnswerStyle());
        }

        // 3 ЭТАП: Переход или конец
        QTimer::singleShot(1000, this, [this, isCorrect]() {
            if (isCorrect) {
                if (engine->currentLevel() < 15) {
                    engine->nextLevel(); // Повышаем уровень в движке
                    updateUI();          // Обновляем интерфейс (тут сбросятся стили)
                } else {
                    on_gameWon();
                }
            } else {
                on_backToMenuBtn_clicked(); // Проиграл
            }
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
    resetStylesAnswerBtn();

    if (level < 15) {
        level++;  // Увеличиваем уровень!
        loadCurrentQuestion();
        ui->valueLevelLbl->setText(QString("Вопрос %1/15").arg(level));
        startCountdown();
        blockClicks = false;
    } else {
        // Игрок выиграл!
        on_gameWon();
    }
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
    if (countdownTimer) {
        countdownTimer->stop();
    }
    // Вызываем этот сигнал ТОЛЬКО если игрок реально нажал "Назад" или проиграл
    emit gameFinished(0);
    this->close(); // Не забудьте точку с запятой!
}

void gamewindow::on_takeMoneyBtn_clicked()
{
    if (countdownTimer) countdownTimer->stop();

    int questionsAnswered = engine->currentLevel() - 1;
    int prizeToTake = 0;

    if (questionsAnswered > 0) {
        // Мы берем приз за ПРЕДЫДУЩИЙ пройденный уровень
        // В нашем списке призы идут от 100 до 1 000 000 (индексы 0-14)
        // Если отвечено на 1 вопрос, берем индекс 0.
        QString s = prizeLevels[15 - questionsAnswered].replace(" ", "");
        prizeToTake = s.toInt();

        QMessageBox::information(this, "Игра окончена",
                                 QString("Вы забрали деньги: %1 руб.").arg(prizeLevels[15 - questionsAnswered]));
    }

    // КЛАДЕМ ДЕНЬГИ В КОШЕЛЕК
    Wallet::instance().addMoney(prizeToTake);

    // Отправляем сигнал (для совместимости со старым кодом окна)
    emit gameFinished(prizeToTake);
    this->close();
}


void gamewindow::on_fiftyFiftyBtn_clicked()
{
    if (fiftyFiftyUsed) return;

    // Собираем индексы неправильных ответов
    QVector<int> wrongIndices;
    for (int i = 0; i < 4; i++) {
        if (i != correctAnswerIndex) {
            wrongIndices.append(i);
        }
    }

    // Перемешиваем с использованием C++11 random
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(wrongIndices.begin(), wrongIndices.end(), g);

    // Скрываем две неправильные кнопки
    for (int i = 0; i < 2 && i < wrongIndices.size(); i++) {
        answerButtons[wrongIndices[i]]->setText("");  // убираем текст
        answerButtons[wrongIndices[i]]->setEnabled(false);  // делаем неактивной
    }

    fiftyFiftyUsed = true;
    ui->fiftyFiftyBtn->setEnabled(false);
    ui->fiftyFiftyBtn->setStyleSheet("background-color: gray; color: darkgray;");
}


void gamewindow::on_audienceBtn_clicked() {
    if (audienceUsed) return;

    int votes[4];
    int remaining = 100;

    // Даем преимущество правильному ответу
    int correctVote = 40 + (rand() % 30);
    votes[correctAnswerIndex] = correctVote;
    remaining -= correctVote;

    // Распределяем остаток между другими
    for(int i = 0; i < 4; i++) {
        if(i == correctAnswerIndex) continue;
        int v = (remaining > 0) ? (rand() % (remaining + 1)) : 0;
        votes[i] = v;
        remaining -= v;
    }
    votes[0] += remaining; // Добавляем остатки первому для суммы 100

    QString result = QString("Зал проголосовал:\nA: %1%\nB: %2%\nC: %3%\nD: %4%")
                         .arg(votes[0]).arg(votes[1]).arg(votes[2]).arg(votes[3]);

    QMessageBox::information(this, "Помощь зала", result);
    audienceUsed = true;
    ui->audienceBtn->setEnabled(false);
    ui->audienceBtn->setStyleSheet("background-color: gray; color: darkgray;");
}



void gamewindow::on_callBtn_clicked()
{
    if (callUsed) return;

    // C++11 random - лучший вариант
    static std::random_device rd;  // Источник энтропии
    static std::mt19937 gen(rd()); // Генератор Mersenne Twister
    static std::uniform_int_distribution<> dis(0, 99); // Распределение 0-99

    // Друг подсказывает с вероятностью 80%
    bool friendIsRight = dis(gen) < 80;

    if (friendIsRight) {
        QMessageBox::information(this, "Звонок другу",
                                 QString("Друг уверен на 80%%: %1")
                                     .arg(answerButtons[correctAnswerIndex]->text()));
    } else {
        // Для выбора неправильного ответа (0-2)
        std::uniform_int_distribution<> wrongDis(0, 2);

        // Собираем индексы неправильных ответов
        QVector<int> wrongIndices;
        for (int i = 0; i < 4; i++) {
            if (i != correctAnswerIndex) {
                wrongIndices.append(i);
            }
        }

        int wrongIndex = wrongIndices[wrongDis(gen)];

        QMessageBox::information(this, "Звонок другу",
                                 QString("Друг сомневается, но думает что это: %1")
                                     .arg(answerButtons[wrongIndex]->text()));
    }

    callUsed = true;
    ui->callBtn->setEnabled(false);
    ui->callBtn->setStyleSheet("background-color: gray; color: darkgray;");
}

void gamewindow::startNewGame()
{
    level = 1;
    currentQuestionIndex = 0;
    blockClicks = false;

    // Рандомизируем вопросы
    randomizeQuestions();

    // Загружаем первый вопрос
    loadCurrentQuestion();

    ui->valueLevelLbl->setText("Вопрос 1/15");
    startCountdown();
}

void gamewindow::randomizeQuestions()
{
    int questionsNeeded = 15;
    int available = allQuestions.size();

    if (available < questionsNeeded) {
        QMessageBox::warning(this, "Внимание",
                             QString("Недостаточно вопросов! Нужно: %1, доступно: %2")
                                 .arg(questionsNeeded).arg(available));
        questionsNeeded = available;
    }

    // Создаем копию всех вопросов
    QVector<Question> temp = allQuestions;
    gameQuestions.clear();

    // Перемешиваем вопросы
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(temp.begin(), temp.end(), g);

    // Берем нужное количество вопросов
    for (int i = 0; i < questionsNeeded; i++) {
        gameQuestions.append(temp[i]);
    }
}

void gamewindow::loadCurrentQuestion()
{
    if (currentQuestionIndex >= gameQuestions.size()) {
        on_gameWon();
        return;
    }

    const Question& q = gameQuestions[currentQuestionIndex];

    // Показываем вопрос
    ui->questionLbl->setText(q.text);

    // Показываем варианты ответов
    for (int i = 0; i < 4; i++) {
        answerButtons[i]->setText(q.answers[i]);
        answerButtons[i]->setStyleSheet(baseAnswerStyle());
        answerButtons[i]->setEnabled(true);  // Включаем кнопку
        answerButtons[i]->setVisible(true);  // Делаем видимой
    }

    // Сохраняем правильный ответ
    correctAnswerIndex = q.correctIndex;

    // Проверяем, что индекс в правильном диапазоне
    if (correctAnswerIndex < 0 || correctAnswerIndex > 3) {
        QMessageBox::warning(this, "Ошибка вопроса",
                             QString("Вопрос '%1' имеет некорректный индекс правильного ответа: %2. Установлен 0.")
                                 .arg(q.text.left(50))
                                 .arg(correctAnswerIndex));
        correctAnswerIndex = 0;
    }

    // Обновляем список призов
    if (level <= 15) {
        ui->prizeList->setCurrentRow(15 - level);
    }
}

QPushButton* gamewindow::getCorrectButton()
{
    // Проверяем, что индекс в допустимом диапазоне
    if (correctAnswerIndex >= 0 && correctAnswerIndex <= 3 &&
        correctAnswerIndex < answerButtons.size()) {
        return answerButtons[correctAnswerIndex];
    }

    // Если что-то пошло не так, показываем сообщение
    QMessageBox::warning(this, "Ошибка",
                         QString("Некорректный индекс правильного ответа: %1")
                             .arg(correctAnswerIndex));

    // Возвращаем первую кнопку как fallback
    return ui->answerBtn1;
}

void gamewindow::on_gameWon()
{
    if (countdownTimer) {
        countdownTimer->stop();
        countdownTimer->deleteLater();
        countdownTimer = nullptr;
    }

    QMessageBox::information(this, "Победа!", "Поздравляем! Вы выиграли 1 000 000 рублей!");

    // Отправляем максимальный приз (1 000 000 рублей)
    QString maxPrize = prizeLevels[0].replace(" ", "");
    bool ok;
    int prizeMoney = maxPrize.toInt(&ok);
    if (ok) {
        emit gameFinished(prizeMoney);
    }

    on_backToMenuBtn_clicked();
}

void gamewindow::on_gameLost()
{
    // Останавливаем таймер
    if (countdownTimer) {
        countdownTimer->stop();
        countdownTimer->deleteLater();
        countdownTimer = nullptr;
    }
    QMessageBox::information(this, "Проигрыш", "К сожалению, вы проиграли!");
    on_backToMenuBtn_clicked();
}
