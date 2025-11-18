#ifndef STYLES_H
#define STYLES_H

#include <QString>

// базовый стиль
QString baseAnswerStyle();

// универсальный стиль
QString answerStyle(const QString& backgroundColor, const QString& textColor);

// стили для состояний
QString correctAnswerStyle();
QString wrongAnswerStyle();
QString blinkAnswerStyle();

QString hintButtonStyle();


#endif // STYLES_H
