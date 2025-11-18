#include "styles.h"

QString baseAnswerStyle() {
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

QString answerStyle(const QString& backgroundColor, const QString& textColor) {
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
    )").arg(backgroundColor, textColor);
}

QString correctAnswerStyle() {
    return answerStyle("#4caf50", "white"); // зелёный
}

QString wrongAnswerStyle() {
    return answerStyle("#f44336", "white"); // красный
}

QString blinkAnswerStyle() {
    return answerStyle("#FFD700", "black"); // ярко-жёлтый
}

QString hintButtonStyle() {
    return R"(
        QPushButton {
            background-color: #87CEFA; /* светло-голубой */
            color: #1e1e1e;
            font: bold 14px "Segoe UI";
            border: 2px solid #5aaedc;
            border-radius: 6px;
            padding: 8px 12px;
            text-align: center;
        }
        QPushButton:hover {
            background-color: #add8e6; /* немного светлее при наведении */
            border-color: #3399cc;
        }
        QPushButton:pressed {
            background-color: #5aaedc; /* насыщенный голубой при нажатии */
            color: white;
            border-color: #2a8bbf;
        }
    )";
}
