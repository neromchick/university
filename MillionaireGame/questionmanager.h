#ifndef QUESTIONMANAGER_H
#define QUESTIONMANAGER_H

#include <QVector>
#include <QString>
#include "question.h"

class QuestionManager {
public:
    bool loadQuestions(const QString& filename);
    QVector<Question> getRandomQuestions(int count);

private:
    QVector<Question> allQuestions;
};

#endif // QUESTIONMANAGER_H
