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
#include <QtWidgets/QFrame>
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
    QFrame *frame;
    QLabel *balLbl_2;
    QLabel *balanceLbl;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *startwindow)
    {
        if (startwindow->objectName().isEmpty())
            startwindow->setObjectName("startwindow");
        startwindow->resize(484, 538);
        centralwidget = new QWidget(startwindow);
        centralwidget->setObjectName("centralwidget");
        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName("startBtn");
        startBtn->setGeometry(QRect(140, 200, 211, 81));
        exitBtn = new QPushButton(centralwidget);
        exitBtn->setObjectName("exitBtn");
        exitBtn->setGeometry(QRect(140, 340, 211, 81));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(170, 10, 311, 51));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        balLbl_2 = new QLabel(frame);
        balLbl_2->setObjectName("balLbl_2");
        balLbl_2->setGeometry(QRect(10, 10, 91, 31));
        QFont font;
        font.setPointSize(16);
        balLbl_2->setFont(font);
        balanceLbl = new QLabel(frame);
        balanceLbl->setObjectName("balanceLbl");
        balanceLbl->setGeometry(QRect(110, 11, 191, 31));
        balanceLbl->setFont(font);
        startwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(startwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 484, 25));
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
        balLbl_2->setText(QCoreApplication::translate("startwindow", "\320\221\320\260\320\273\320\260\320\275\321\201:", nullptr));
        balanceLbl->setText(QCoreApplication::translate("startwindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startwindow: public Ui_startwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
