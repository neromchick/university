/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewindow
{
public:
    QWidget *centralwidget;
    QPushButton *answerBtn1;
    QPushButton *answerBtn2;
    QPushButton *answerBtn3;
    QPushButton *answerBtn4;
    QPushButton *fiftyFiftyBtn;
    QPushButton *audienceBtn;
    QPushButton *callBtn;
    QPushButton *takeMoneyBtn;
    QPushButton *backToMenuBtn;
    QListWidget *prizeList;
    QFrame *frame;
    QLabel *questionLbl;
    QLabel *valueLevelLbl;
    QLabel *countdownLbl;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gamewindow)
    {
        if (gamewindow->objectName().isEmpty())
            gamewindow->setObjectName("gamewindow");
        gamewindow->resize(800, 600);
        centralwidget = new QWidget(gamewindow);
        centralwidget->setObjectName("centralwidget");
        answerBtn1 = new QPushButton(centralwidget);
        answerBtn1->setObjectName("answerBtn1");
        answerBtn1->setGeometry(QRect(20, 340, 231, 81));
        answerBtn2 = new QPushButton(centralwidget);
        answerBtn2->setObjectName("answerBtn2");
        answerBtn2->setGeometry(QRect(320, 340, 231, 81));
        answerBtn3 = new QPushButton(centralwidget);
        answerBtn3->setObjectName("answerBtn3");
        answerBtn3->setGeometry(QRect(20, 450, 231, 81));
        answerBtn4 = new QPushButton(centralwidget);
        answerBtn4->setObjectName("answerBtn4");
        answerBtn4->setGeometry(QRect(320, 440, 231, 81));
        fiftyFiftyBtn = new QPushButton(centralwidget);
        fiftyFiftyBtn->setObjectName("fiftyFiftyBtn");
        fiftyFiftyBtn->setGeometry(QRect(120, 20, 91, 81));
        audienceBtn = new QPushButton(centralwidget);
        audienceBtn->setObjectName("audienceBtn");
        audienceBtn->setGeometry(QRect(230, 20, 91, 81));
        callBtn = new QPushButton(centralwidget);
        callBtn->setObjectName("callBtn");
        callBtn->setGeometry(QRect(340, 20, 91, 81));
        takeMoneyBtn = new QPushButton(centralwidget);
        takeMoneyBtn->setObjectName("takeMoneyBtn");
        takeMoneyBtn->setGeometry(QRect(450, 20, 201, 71));
        backToMenuBtn = new QPushButton(centralwidget);
        backToMenuBtn->setObjectName("backToMenuBtn");
        backToMenuBtn->setGeometry(QRect(20, 50, 90, 29));
        prizeList = new QListWidget(centralwidget);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        new QListWidgetItem(prizeList);
        prizeList->setObjectName("prizeList");
        prizeList->setGeometry(QRect(660, 30, 131, 511));
        prizeList->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"        background-color: #111;\n"
"        color: white;\n"
"        font: bold 16px \"Segoe UI\";\n"
"        border: none;\n"
"    }\n"
"    QListWidget::item {\n"
"        padding: 4px;\n"
"        border-bottom: 1px solid #333;\n"
"    }\n"
"    QListWidget::item:selected {\n"
"        background-color: #ff9800;\n"
"        color: black;\n"
"    }\n"
"QListWidget {\n"
"        border: none;\n"
"        padding: 0px;\n"
"        margin: 0px;\n"
"        spacing: 0px;\n"
"    }\n"
""));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 120, 531, 201));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        questionLbl = new QLabel(frame);
        questionLbl->setObjectName("questionLbl");
        questionLbl->setGeometry(QRect(0, 70, 531, 131));
        QFont font;
        font.setPointSize(14);
        questionLbl->setFont(font);
        questionLbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        valueLevelLbl = new QLabel(frame);
        valueLevelLbl->setObjectName("valueLevelLbl");
        valueLevelLbl->setGeometry(QRect(0, 0, 531, 41));
        valueLevelLbl->setFont(font);
        valueLevelLbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        countdownLbl = new QLabel(frame);
        countdownLbl->setObjectName("countdownLbl");
        countdownLbl->setGeometry(QRect(410, 10, 63, 20));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 350, 41, 51));
        QFont font1;
        font1.setPointSize(28);
        label->setFont(font1);
        gamewindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gamewindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        gamewindow->setMenuBar(menubar);
        statusbar = new QStatusBar(gamewindow);
        statusbar->setObjectName("statusbar");
        gamewindow->setStatusBar(statusbar);

        retranslateUi(gamewindow);

        QMetaObject::connectSlotsByName(gamewindow);
    } // setupUi

    void retranslateUi(QMainWindow *gamewindow)
    {
        gamewindow->setWindowTitle(QCoreApplication::translate("gamewindow", "MainWindow", nullptr));
        answerBtn1->setText(QCoreApplication::translate("gamewindow", "\320\236\320\242\320\222\320\225\320\242 1", nullptr));
        answerBtn2->setText(QCoreApplication::translate("gamewindow", "PushButton", nullptr));
        answerBtn3->setText(QCoreApplication::translate("gamewindow", "PushButton", nullptr));
        answerBtn4->setText(QCoreApplication::translate("gamewindow", "PushButton", nullptr));
        fiftyFiftyBtn->setText(QCoreApplication::translate("gamewindow", "PushButton", nullptr));
        audienceBtn->setText(QCoreApplication::translate("gamewindow", "PushButton", nullptr));
        callBtn->setText(QCoreApplication::translate("gamewindow", "PushButton", nullptr));
        takeMoneyBtn->setText(QCoreApplication::translate("gamewindow", "PushButton", nullptr));
        backToMenuBtn->setText(QCoreApplication::translate("gamewindow", "PushButton", nullptr));

        const bool __sortingEnabled = prizeList->isSortingEnabled();
        prizeList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = prizeList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("gamewindow", "1000000", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = prizeList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("gamewindow", "700000", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = prizeList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("gamewindow", "400000", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = prizeList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("gamewindow", "200000", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = prizeList->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("gamewindow", "100000", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = prizeList->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("gamewindow", "50000", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = prizeList->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("gamewindow", "25000", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = prizeList->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("gamewindow", "15000", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = prizeList->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("gamewindow", "10000", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = prizeList->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("gamewindow", "5000", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = prizeList->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("gamewindow", "2000", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = prizeList->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("gamewindow", "1000", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = prizeList->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("gamewindow", "500", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = prizeList->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("gamewindow", "200", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = prizeList->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("gamewindow", "100", nullptr));
        prizeList->setSortingEnabled(__sortingEnabled);

        questionLbl->setText(QCoreApplication::translate("gamewindow", "TextLabel", nullptr));
        valueLevelLbl->setText(QCoreApplication::translate("gamewindow", "\320\222\320\276\320\277\321\200\320\276\321\201 1/15", nullptr));
        countdownLbl->setText(QCoreApplication::translate("gamewindow", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("gamewindow", "A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewindow: public Ui_gamewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
