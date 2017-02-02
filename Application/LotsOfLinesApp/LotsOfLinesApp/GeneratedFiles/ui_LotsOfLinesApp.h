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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LotsOfLinesAppClass
{
public:
    QAction *actionLoad;
    QAction *actionWindows;
    QAction *actionVisualization_Options;
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
    QGroupBox *visualizationOptionsGroupBox;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_3;
    QToolBox *toolBox;
    QWidget *page;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QDockWidget *dataTableDock;
    QWidget *dockWidgetContents_2;

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
        centralWidget = new QWidget(LotsOfLinesAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralLayout = new QGridLayout(centralWidget);
        centralLayout->setSpacing(6);
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 185, 480));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        visualizationOptionsGroupBox = new QGroupBox(scrollAreaWidgetContents);
        visualizationOptionsGroupBox->setObjectName(QStringLiteral("visualizationOptionsGroupBox"));
        visualizationOptionsGroupBox->setStyleSheet(QStringLiteral(""));
        verticalLayout_3 = new QVBoxLayout(visualizationOptionsGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        toolBox = new QToolBox(visualizationOptionsGroupBox);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setStyleSheet(QLatin1String("QToolBox{\n"
"	color: rgb(205, 205, 205);\n"
"}"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 147, 104));
        verticalLayout_4 = new QVBoxLayout(page);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        checkBox_3 = new QCheckBox(page);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        verticalLayout_4->addWidget(checkBox_3);

        checkBox_2 = new QCheckBox(page);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout_4->addWidget(checkBox_2);

        checkBox_4 = new QCheckBox(page);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        verticalLayout_4->addWidget(checkBox_4);

        checkBox = new QCheckBox(page);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_4->addWidget(checkBox);

        toolBox->addItem(page, QStringLiteral("Display"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, -26, 130, 99));
        verticalLayout_5 = new QVBoxLayout(page_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        pushButton_2 = new QPushButton(page_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setStyleSheet(QLatin1String("QPushButton{\n"
"	background-color: rgb(100,100, 100);\n"
"}"));

        verticalLayout_5->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setStyleSheet(QStringLiteral(""));

        verticalLayout_5->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(page_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout_5->addWidget(pushButton_4);

        toolBox->addItem(page_2, QStringLiteral("Lines"));

        verticalLayout_3->addWidget(toolBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        label = new QLabel(visualizationOptionsGroupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 54));
        label->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(label);

        comboBox = new QComboBox(visualizationOptionsGroupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_3->addWidget(comboBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        pushButton = new QPushButton(visualizationOptionsGroupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_3->addWidget(pushButton);


        verticalLayout_2->addWidget(visualizationOptionsGroupBox);

        sidebarScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(sidebarScrollArea);

        sidebarDockWidget->setWidget(dockWidgetContents);
        LotsOfLinesAppClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), sidebarDockWidget);
        dataTableDock = new QDockWidget(LotsOfLinesAppClass);
        dataTableDock->setObjectName(QStringLiteral("dataTableDock"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dataTableDock->setWidget(dockWidgetContents_2);
        LotsOfLinesAppClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dataTableDock);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionLoad);

        retranslateUi(LotsOfLinesAppClass);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LotsOfLinesAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *LotsOfLinesAppClass)
    {
        LotsOfLinesAppClass->setWindowTitle(QApplication::translate("LotsOfLinesAppClass", "LotsOfLinesApp", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("LotsOfLinesAppClass", "Load", Q_NULLPTR));
        actionWindows->setText(QApplication::translate("LotsOfLinesAppClass", "Windows", Q_NULLPTR));
        actionVisualization_Options->setText(QApplication::translate("LotsOfLinesAppClass", "Visualization Options", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("LotsOfLinesAppClass", "File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("LotsOfLinesAppClass", "View", Q_NULLPTR));
        sidebarDockWidget->setWindowTitle(QApplication::translate("LotsOfLinesAppClass", "Menu Bar", Q_NULLPTR));
        visualizationOptionsGroupBox->setTitle(QApplication::translate("LotsOfLinesAppClass", "Visualization Type", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("LotsOfLinesAppClass", "Radial Paired", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("LotsOfLinesAppClass", "Shifted Paired", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("LotsOfLinesAppClass", "Collocated Coordinate", Q_NULLPTR));
        checkBox->setText(QApplication::translate("LotsOfLinesAppClass", "Parallel Coordinate", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("LotsOfLinesAppClass", "Display", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("LotsOfLinesAppClass", "Remove Line", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("LotsOfLinesAppClass", "Show Line", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("LotsOfLinesAppClass", "Isolate Line", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("LotsOfLinesAppClass", "Lines", Q_NULLPTR));
        label->setText(QApplication::translate("LotsOfLinesAppClass", "Line Orientation", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("LotsOfLinesAppClass", "Normal", Q_NULLPTR)
         << QApplication::translate("LotsOfLinesAppClass", "PC Adaptation", Q_NULLPTR)
         << QApplication::translate("LotsOfLinesAppClass", "Non-PC", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("LotsOfLinesAppClass", "Load File", Q_NULLPTR));
        dataTableDock->setWindowTitle(QApplication::translate("LotsOfLinesAppClass", "Data Table", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LotsOfLinesAppClass: public Ui_LotsOfLinesAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOTSOFLINESAPP_H
