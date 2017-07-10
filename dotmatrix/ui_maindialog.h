/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainDialog
{
public:
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *mainDialog)
    {
        if (mainDialog->objectName().isEmpty())
            mainDialog->setObjectName(QStringLiteral("mainDialog"));
        mainDialog->resize(884, 434);
        mainDialog->setStyleSheet(QStringLiteral("background-image: url(:/images/about.png);"));
        centralWidget = new QWidget(mainDialog);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mainDialog->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(mainDialog);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainDialog->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainDialog);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainDialog->setStatusBar(statusBar);
        menuBar = new QMenuBar(mainDialog);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 884, 21));
        mainDialog->setMenuBar(menuBar);

        retranslateUi(mainDialog);

        QMetaObject::connectSlotsByName(mainDialog);
    } // setupUi

    void retranslateUi(QMainWindow *mainDialog)
    {
        mainDialog->setWindowTitle(QApplication::translate("mainDialog", "About", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainDialog: public Ui_mainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
