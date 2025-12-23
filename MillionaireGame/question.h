#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QStringList>

class Question {
public:
    Question() : correctIndex(-1) {}

    QString text;
    QString answers[4];
    int correctIndex;
};

#endif // QUESTION_H
