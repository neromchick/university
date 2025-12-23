#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) : QObject(parent) {
    m_level = 1;
    m_gameOver = false;

    // Таблица призов (от 100 до 1 000 000)
    m_prizeTable << "100" << "200" << "500" << "1 000" << "2 000"
                 << "5 000" << "10 000" << "15 000" << "25 000" << "50 000"
                 << "100 000" << "200 000" << "400 000" << "700 000" << "1 000 000";
}

void GameEngine::startNewGame(const QVector<Question>& questions) {
    m_questions = questions;
    m_level = 1;
    m_gameOver = false;
    emit levelPassed(); // Сигнал для UI, чтобы загрузить первый вопрос
}

bool GameEngine::checkAnswer(int index) {
    if (m_level <= 0 || m_level > m_questions.size()) return false;

    // Сверяем ответ
    if (index == m_questions[m_level - 1].correctIndex) {
        return true;
    }
    return false;
}

Question GameEngine::currentQuestion() const {
    if (m_level <= m_questions.size()) {
        return m_questions[m_level - 1];
    }
    return Question();
}

int GameEngine::currentPrize() const {
    if (m_level > 0 && m_level <= m_prizeTable.size()) {
        QString s = m_prizeTable.at(m_level - 1);

        s.replace(" ", "");

        return s.toInt();
    }
    return 0;
}

void GameEngine::nextLevel() {
    if (m_level < 15) {
        m_level++;
    }
}
