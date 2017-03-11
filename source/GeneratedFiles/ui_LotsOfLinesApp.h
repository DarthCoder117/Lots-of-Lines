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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LotsOfLinesAppClass
{
public:
    QAction *actionLoad;
    QAction *actionWindows;
    QAction *actionVisualization_Options;
    QAction *actionPreferences;
    QWidget *centralWidget;
    QGridLayout *centralLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QStatusBar *statusBar;
    QDockWidget *sidebarDockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QScrollArea *sidebarScrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *visualizationTypeArea;
    QVBoxLayout *visualizationTypeLayout;
    QScrollArea *optionsScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *optionsScrollLayout;
    QPushButton *loadFileButton;
    QDockWidget *dataTableDock;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout;
    QTabWidget *dataClassTabs;

    void setupUi(QMainWindow *LotsOfLinesAppClass)
    {
        if (LotsOfLinesAppClass->objectName().isEmpty())
            LotsOfLinesAppClass->setObjectName(QStringLiteral("LotsOfLinesAppClass"));
        LotsOfLinesAppClass->resize(1095, 587);
        actionLoad = new QAction(LotsOfLinesAppClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionWindows = new QAction(LotsOfLinesAppClass);
        actionWindows->setObjectName(QStringLiteral("actionWindows"));
        actionVisualization_Options = new QAction(LotsOfLinesAppClass);
        actionVisualization_Options->setObjectName(QStringLiteral("actionVisualization_Options"));
        actionVisualization_Options->setCheckable(true);
        actionPreferences = new QAction(LotsOfLinesAppClass);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        centralWidget = new QWidget(LotsOfLinesAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralLayout = new QGridLayout(centralWidget);
        centralLayout->setSpacing(2);
        centralLayout->setContentsMargins(11, 11, 11, 11);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));
        centralLayout->setContentsMargins(0, 0, 0, 0);
        LotsOfLinesAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LotsOfLinesAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1095, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        LotsOfLinesAppClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(LotsOfLinesAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LotsOfLinesAppClass->setStatusBar(statusBar);
        sidebarDockWidget = new QDockWidget(LotsOfLinesAppClass);
        sidebarDockWidget->setObjectName(QStringLiteral("sidebarDockWidget"));
        sidebarDockWidget->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(0, 100, 254);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"QDockWidget{\n"
"	background-color: rgb(225, 225, 225);\n"
"	page-color: rgb(200,200,200);\n"
"}\n"
"QGroupBox{\n"
"	background-color: rgb(225,225,225);\n"
"}\n"
"QToolBox{\n"
"	page-color:rgb(205,205,205);\n"
"}\n"
"QCheckBox{\n"
"	color: rgb(25,25,25);\n"
"}\n"
""));
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 122, 472));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        visualizationTypeArea = new QGroupBox(scrollAreaWidgetContents);
        visualizationTypeArea->setObjectName(QStringLiteral("visualizationTypeArea"));
        visualizationTypeArea->setStyleSheet(QStringLiteral(""));
        visualizationTypeArea->setFlat(false);
        visualizationTypeLayout = new QVBoxLayout(visualizationTypeArea);
        visualizationTypeLayout->setSpacing(6);
        visualizationTypeLayout->setContentsMargins(11, 11, 11, 11);
        visualizationTypeLayout->setObjectName(QStringLiteral("visualizationTypeLayout"));

        verticalLayout_2->addWidget(visualizationTypeArea);

        optionsScrollArea = new QScrollArea(scrollAreaWidgetContents);
        optionsScrollArea->setObjectName(QStringLiteral("optionsScrollArea"));
        optionsScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 102, 384));
        optionsScrollLayout = new QVBoxLayout(scrollAreaWidgetContents_2);
        optionsScrollLayout->setSpacing(6);
        optionsScrollLayout->setContentsMargins(11, 11, 11, 11);
        optionsScrollLayout->setObjectName(QStringLiteral("optionsScrollLayout"));
        optionsScrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_2->addWidget(optionsScrollArea);

        loadFileButton = new QPushButton(scrollAreaWidgetContents);
        loadFileButton->setObjectName(QStringLiteral("loadFileButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loadFileButton->sizePolicy().hasHeightForWidth());
        loadFileButton->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(loadFileButton);

        sidebarScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(sidebarScrollArea);

        sidebarDockWidget->setWidget(dockWidgetContents);
        LotsOfLinesAppClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), sidebarDockWidget);
        dataTableDock = new QDockWidget(LotsOfLinesAppClass);
        dataTableDock->setObjectName(QStringLiteral("dataTableDock"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        gridLayout = new QGridLayout(dockWidgetContents_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        dataClassTabs = new QTabWidget(dockWidgetContents_2);
        dataClassTabs->setObjectName(QStringLiteral("dataClassTabs"));

        gridLayout->addWidget(dataClassTabs, 0, 0, 1, 1);

        dataTableDock->setWidget(dockWidgetContents_2);
        LotsOfLinesAppClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dataTableDock);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionPreferences);

        retranslateUi(LotsOfLinesAppClass);
        QObject::connect(loadFileButton, SIGNAL(clicked()), actionLoad, SLOT(trigger()));

        dataClassTabs->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(LotsOfLinesAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *LotsOfLinesAppClass)
    {
        LotsOfLinesAppClass->setWindowTitle(QApplication::translate("LotsOfLinesAppClass", "LotsOfLinesApp", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("LotsOfLinesAppClass", "Load", Q_NULLPTR));
        actionWindows->setText(QApplication::translate("LotsOfLinesAppClass", "Windows", Q_NULLPTR));
        actionVisualization_Options->setText(QApplication::translate("LotsOfLinesAppClass", "Visualization Options", Q_NULLPTR));
        actionPreferences->setText(QApplication::translate("LotsOfLinesAppClass", "Preferences", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("LotsOfLinesAppClass", "File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("LotsOfLinesAppClass", "View", Q_NULLPTR));
        sidebarDockWidget->setWindowTitle(QApplication::translate("LotsOfLinesAppClass", "Menu Bar", Q_NULLPTR));
        visualizationTypeArea->setTitle(QApplication::translate("LotsOfLinesAppClass", "Visualization Type", Q_NULLPTR));
        loadFileButton->setText(QApplication::translate("LotsOfLinesAppClass", "Load File", Q_NULLPTR));
        dataTableDock->setWindowTitle(QApplication::translate("LotsOfLinesAppClass", "Data Table", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LotsOfLinesAppClass: public Ui_LotsOfLinesAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOTSOFLINESAPP_H
