/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startwindow
{
public:
    QWidget *centralwidget;
    QPushButton *startBtn;
    QPushButton *exitBtn;
    QLabel *balanceLbl;
    QLabel *balLbl_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *startwindow)
    {
        if (startwindow->objectName().isEmpty())
            startwindow->setObjectName("startwindow");
        startwindow->resize(800, 600);
        centralwidget = new QWidget(startwindow);
        centralwidget->setObjectName("centralwidget");
        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName("startBtn");
        startBtn->setGeometry(QRect(320, 260, 161, 81));
        exitBtn = new QPushButton(centralwidget);
        exitBtn->setObjectName("exitBtn");
        exitBtn->setGeometry(QRect(320, 370, 161, 81));
        balanceLbl = new QLabel(centralwidget);
        balanceLbl->setObjectName("balanceLbl");
        balanceLbl->setGeometry(QRect(600, 21, 191, 31));
        QFont font;
        font.setPointSize(16);
        balanceLbl->setFont(font);
        balLbl_2 = new QLabel(centralwidget);
        balLbl_2->setObjectName("balLbl_2");
        balLbl_2->setGeometry(QRect(500, 20, 91, 31));
        balLbl_2->setFont(font);
        startwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(startwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        startwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(startwindow);
        statusbar->setObjectName("statusbar");
        startwindow->setStatusBar(statusbar);

        retranslateUi(startwindow);

        QMetaObject::connectSlotsByName(startwindow);
    } // setupUi

    void retranslateUi(QMainWindow *startwindow)
    {
        startwindow->setWindowTitle(QCoreApplication::translate("startwindow", "MainWindow", nullptr));
        startBtn->setText(QCoreApplication::translate("startwindow", "\320\241\320\242\320\220\320\240\320\242", nullptr));
        exitBtn->setText(QCoreApplication::translate("startwindow", "\320\222\320\253\320\245\320\236\320\224", nullptr));
        balanceLbl->setText(QCoreApplication::translate("startwindow", "0", nullptr));
        balLbl_2->setText(QCoreApplication::translate("startwindow", "\320\221\320\260\320\273\320\260\320\275\321\201:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startwindow: public Ui_startwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
