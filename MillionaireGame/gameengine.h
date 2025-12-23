#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QStringList>
#include "question.h"

class GameEngine : public QObject {
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);

    void startNewGame(const QVector<Question>& questions);
    bool checkAnswer(int index);
    void nextLevel();

    // Геттеры
    int currentLevel() const { return m_level; }
    int currentPrize() const;
    Question currentQuestion() const;
    bool isGameOver() const { return m_gameOver; }

signals:
    void levelPassed();
    void gameWon(int finalPrize);
    void gameLost();

private:
    QVector<Question> m_questions;
    int m_level;
    bool m_gameOver;
    QStringList m_prizeTable;
};

#endif
