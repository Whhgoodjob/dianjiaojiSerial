/********************************************************************************
** Form generated from reading UI file 'SerialHelper.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALHELPER_H
#define UI_SERIALHELPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialHelperClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SerialHelperClass)
    {
        if (SerialHelperClass->objectName().isEmpty())
            SerialHelperClass->setObjectName("SerialHelperClass");
        SerialHelperClass->resize(600, 400);
        menuBar = new QMenuBar(SerialHelperClass);
        menuBar->setObjectName("menuBar");
        SerialHelperClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SerialHelperClass);
        mainToolBar->setObjectName("mainToolBar");
        SerialHelperClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SerialHelperClass);
        centralWidget->setObjectName("centralWidget");
        SerialHelperClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SerialHelperClass);
        statusBar->setObjectName("statusBar");
        SerialHelperClass->setStatusBar(statusBar);

        retranslateUi(SerialHelperClass);

        QMetaObject::connectSlotsByName(SerialHelperClass);
    } // setupUi

    void retranslateUi(QMainWindow *SerialHelperClass)
    {
        SerialHelperClass->setWindowTitle(QCoreApplication::translate("SerialHelperClass", "SerialHelper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialHelperClass: public Ui_SerialHelperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALHELPER_H
