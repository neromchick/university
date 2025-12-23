#include "questionmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>
#include <random>

bool QuestionManager::loadQuestions(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isArray()) return false;

    QJsonArray array = doc.array();
    allQuestions.clear();

    for (const QJsonValue& value : array) {
        QJsonObject obj = value.toObject();
        Question q;

        q.text = obj["question"].toString();

        QJsonArray answersArray = obj["answers"].toArray();
        for (int i = 0; i < 4 && i < answersArray.size(); i++) {
            q.answers[i] = answersArray[i].toString();
        }

        q.correctIndex = obj["correct"].toInt(0);
        // Валидация
        if (q.correctIndex < 0) q.correctIndex = 0;
        if (q.correctIndex > 3) q.correctIndex = 3;

        allQuestions.append(q);
    }
    return !allQuestions.isEmpty();
}

QVector<Question> QuestionManager::getRandomQuestions(int count) {
    QVector<Question> temp = allQuestions;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(temp.begin(), temp.end(), g);

    QVector<Question> result;
    for (int i = 0; i < count && i < temp.size(); ++i) {
        result.append(temp[i]);
    }
    return result;
}
