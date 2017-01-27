/********************************************************************************
** Form generated from reading UI file 'LotsOfLinesApp.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOTSOFLINESAPP_H
#define UI_LOTSOFLINESAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LotsOfLinesAppClass
{
public:
    QAction *actionLoad;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;
    QDockWidget *sidebarDockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QScrollArea *sidebarScrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QMainWindow *LotsOfLinesAppClass)
    {
        if (LotsOfLinesAppClass->objectName().isEmpty())
            LotsOfLinesAppClass->setObjectName(QStringLiteral("LotsOfLinesAppClass"));
        LotsOfLinesAppClass->resize(600, 400);
        actionLoad = new QAction(LotsOfLinesAppClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        centralWidget = new QWidget(LotsOfLinesAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LotsOfLinesAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LotsOfLinesAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        LotsOfLinesAppClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(LotsOfLinesAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LotsOfLinesAppClass->setStatusBar(statusBar);
        sidebarDockWidget = new QDockWidget(LotsOfLinesAppClass);
        sidebarDockWidget->setObjectName(QStringLiteral("sidebarDockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        sidebarScrollArea = new QScrollArea(dockWidgetContents);
        sidebarScrollArea->setObjectName(QStringLiteral("sidebarScrollArea"));
        sidebarScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 119, 335));
        sidebarScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(sidebarScrollArea);

        sidebarDockWidget->setWidget(dockWidgetContents);
        LotsOfLinesAppClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), sidebarDockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad);

        retranslateUi(LotsOfLinesAppClass);

        QMetaObject::connectSlotsByName(LotsOfLinesAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *LotsOfLinesAppClass)
    {
        LotsOfLinesAppClass->setWindowTitle(QApplication::translate("LotsOfLinesAppClass", "LotsOfLinesApp", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("LotsOfLinesAppClass", "Load", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("LotsOfLinesAppClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LotsOfLinesAppClass: public Ui_LotsOfLinesAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOTSOFLINESAPP_H
