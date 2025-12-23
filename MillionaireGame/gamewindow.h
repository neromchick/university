#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <QList>
#include <functional>
#include "gameengine.h"
#include "questionmanager.h"

namespace Ui {
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT

signals:
    void gameFinished(int money);

public:
    explicit gamewindow(QWidget *parent = nullptr);
    ~gamewindow();

private slots:
    // Игровая логика
    void on_answerBtn_clicked();
    void on_hintBtn_clicked();
    void on_backToMenuBtn_clicked();
    void on_takeMoneyBtn_clicked();
    void on_fiftyFiftyBtn_clicked();
    void on_audienceBtn_clicked();
    void on_callBtn_clicked();

    void updateUI();

    // Вспомогательные методы
    void animateBlink(QPushButton* button, int times, int interval,
                      std::function<void()> onFinished = nullptr);
    void startCountdown();
    void resetStylesAnswerBtn();
    void applyStylesHintBtn();
    void proceedToNextLevel();
    void loadNextQuestion();
    void initPrizeList();

private:
    Ui::gamewindow *ui;

    GameEngine* engine;
    QuestionManager* qManager;

    // Основные переменные игры
    int level = 1;
    bool blockClicks = false;
    double countdown = 15.00;
    QTimer* countdownTimer = nullptr;

    bool fiftyFiftyUsed = false;
    bool audienceUsed = false;
    bool callUsed = false;

    // Кнопки
    QList<QPushButton*> answerButtons;
    QList<QPushButton*> hintButtons;

    QVector<Question> allQuestions;   // все вопросы из файла
    QVector<Question> gameQuestions;  // вопросы для текущей игры
    int currentQuestionIndex = 0;
    int correctAnswerIndex = -1;

    // Призы
    QStringList prizeLevels;

    // Методы для работы с вопросами
    void loadQuestionsFromFile(const QString& filename);
    void randomizeQuestions();
    void loadCurrentQuestion();
    void startNewGame();
    QPushButton* getCorrectButton();

    // Завершение игры
    void on_gameWon();
    void on_gameLost();
};

#endif // GAMEWINDOW_H
