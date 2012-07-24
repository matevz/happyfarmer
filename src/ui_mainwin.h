/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created: Tue Jul 24 02:15:30 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "widget/gameview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWin
{
public:
    QAction *actionExit;
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionUltra;
    QAction *actionFast;
    QAction *actionNormal;
    QAction *actionSlow;
    QAction *actionPause;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QToolButton *roadBtn;
    QToolButton *dirtRoadBtn;
    QSpacerItem *verticalSpacer;
    QToolButton *magnifierBtn;
    QToolButton *cursorBtn;
    QLabel *dateLabel;
    HFGameView *gameView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSpeed;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWin)
    {
        if (MainWin->objectName().isEmpty())
            MainWin->setObjectName(QString::fromUtf8("MainWin"));
        MainWin->resize(800, 600);
        actionExit = new QAction(MainWin);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionLoad = new QAction(MainWin);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionSave = new QAction(MainWin);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionUltra = new QAction(MainWin);
        actionUltra->setObjectName(QString::fromUtf8("actionUltra"));
        actionFast = new QAction(MainWin);
        actionFast->setObjectName(QString::fromUtf8("actionFast"));
        actionNormal = new QAction(MainWin);
        actionNormal->setObjectName(QString::fromUtf8("actionNormal"));
        actionSlow = new QAction(MainWin);
        actionSlow->setObjectName(QString::fromUtf8("actionSlow"));
        actionPause = new QAction(MainWin);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        centralwidget = new QWidget(MainWin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        roadBtn = new QToolButton(widget);
        roadBtn->setObjectName(QString::fromUtf8("roadBtn"));

        gridLayout->addWidget(roadBtn, 2, 0, 1, 1);

        dirtRoadBtn = new QToolButton(widget);
        dirtRoadBtn->setObjectName(QString::fromUtf8("dirtRoadBtn"));

        gridLayout->addWidget(dirtRoadBtn, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 465, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        magnifierBtn = new QToolButton(widget);
        magnifierBtn->setObjectName(QString::fromUtf8("magnifierBtn"));

        gridLayout->addWidget(magnifierBtn, 1, 1, 1, 1);

        cursorBtn = new QToolButton(widget);
        cursorBtn->setObjectName(QString::fromUtf8("cursorBtn"));

        gridLayout->addWidget(cursorBtn, 1, 0, 1, 1);

        dateLabel = new QLabel(widget);
        dateLabel->setObjectName(QString::fromUtf8("dateLabel"));

        gridLayout->addWidget(dateLabel, 0, 0, 1, 2);


        horizontalLayout->addWidget(widget);

        gameView = new HFGameView(centralwidget);
        gameView->setObjectName(QString::fromUtf8("gameView"));

        horizontalLayout->addWidget(gameView);

        MainWin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWin);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSpeed = new QMenu(menubar);
        menuSpeed->setObjectName(QString::fromUtf8("menuSpeed"));
        MainWin->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWin);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWin->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSpeed->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuSpeed->addAction(actionUltra);
        menuSpeed->addAction(actionFast);
        menuSpeed->addAction(actionNormal);
        menuSpeed->addAction(actionSlow);
        menuSpeed->addAction(actionPause);

        retranslateUi(MainWin);

        QMetaObject::connectSlotsByName(MainWin);
    } // setupUi

    void retranslateUi(QMainWindow *MainWin)
    {
        MainWin->setWindowTitle(QApplication::translate("MainWin", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWin", "Exit", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("MainWin", "Load game", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWin", "Save game", 0, QApplication::UnicodeUTF8));
        actionUltra->setText(QApplication::translate("MainWin", "Ultra", 0, QApplication::UnicodeUTF8));
        actionFast->setText(QApplication::translate("MainWin", "Fast", 0, QApplication::UnicodeUTF8));
        actionNormal->setText(QApplication::translate("MainWin", "Normal", 0, QApplication::UnicodeUTF8));
        actionSlow->setText(QApplication::translate("MainWin", "Slow", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate("MainWin", "Pause", 0, QApplication::UnicodeUTF8));
        roadBtn->setText(QApplication::translate("MainWin", "R", 0, QApplication::UnicodeUTF8));
        dirtRoadBtn->setText(QApplication::translate("MainWin", "D", 0, QApplication::UnicodeUTF8));
        magnifierBtn->setText(QApplication::translate("MainWin", "M", 0, QApplication::UnicodeUTF8));
        cursorBtn->setText(QApplication::translate("MainWin", "C", 0, QApplication::UnicodeUTF8));
        dateLabel->setText(QApplication::translate("MainWin", "27th Jul 2012", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWin", "File", 0, QApplication::UnicodeUTF8));
        menuSpeed->setTitle(QApplication::translate("MainWin", "Speed", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWin: public Ui_MainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H
