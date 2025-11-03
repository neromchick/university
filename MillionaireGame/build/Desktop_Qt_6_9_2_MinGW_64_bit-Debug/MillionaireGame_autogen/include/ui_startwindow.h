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
    } // retranslateUi

};

namespace Ui {
    class startwindow: public Ui_startwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
