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
#include <QtWidgets/QRadioButton>
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
    QGridLayout *centralLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;
    QDockWidget *sidebarDockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QScrollArea *sidebarScrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *visualizationOptionsGroupBox;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QButtonGroup *visualizationTypeButtonGroup;

    void setupUi(QMainWindow *LotsOfLinesAppClass)
    {
        if (LotsOfLinesAppClass->objectName().isEmpty())
            LotsOfLinesAppClass->setObjectName(QStringLiteral("LotsOfLinesAppClass"));
        LotsOfLinesAppClass->resize(1095, 587);
        actionLoad = new QAction(LotsOfLinesAppClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 160, 522));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        visualizationOptionsGroupBox = new QGroupBox(scrollAreaWidgetContents);
        visualizationOptionsGroupBox->setObjectName(QStringLiteral("visualizationOptionsGroupBox"));
        verticalLayout_3 = new QVBoxLayout(visualizationOptionsGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        radioButton_2 = new QRadioButton(visualizationOptionsGroupBox);
        visualizationTypeButtonGroup = new QButtonGroup(LotsOfLinesAppClass);
        visualizationTypeButtonGroup->setObjectName(QStringLiteral("visualizationTypeButtonGroup"));
        visualizationTypeButtonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout_3->addWidget(radioButton_2);

        radioButton = new QRadioButton(visualizationOptionsGroupBox);
        visualizationTypeButtonGroup->addButton(radioButton);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout_3->addWidget(radioButton);


        verticalLayout_2->addWidget(visualizationOptionsGroupBox);

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
        sidebarDockWidget->setWindowTitle(QApplication::translate("LotsOfLinesAppClass", "Visualization Options", Q_NULLPTR));
        visualizationOptionsGroupBox->setTitle(QApplication::translate("LotsOfLinesAppClass", "Visualization Type", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("LotsOfLinesAppClass", "Parallel Coordinates", Q_NULLPTR));
        radioButton->setText(QApplication::translate("LotsOfLinesAppClass", "Colocated Paired", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LotsOfLinesAppClass: public Ui_LotsOfLinesAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOTSOFLINESAPP_H
