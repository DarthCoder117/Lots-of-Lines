/********************************************************************************
** Form generated from reading UI file 'PreferencesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *preferencesTabs;
    QWidget *inputTab;
    QWidget *renderingTab;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QStringLiteral("PreferencesDialog"));
        PreferencesDialog->resize(379, 387);
        verticalLayout = new QVBoxLayout(PreferencesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        preferencesTabs = new QTabWidget(PreferencesDialog);
        preferencesTabs->setObjectName(QStringLiteral("preferencesTabs"));
        inputTab = new QWidget();
        inputTab->setObjectName(QStringLiteral("inputTab"));
        preferencesTabs->addTab(inputTab, QString());
        renderingTab = new QWidget();
        renderingTab->setObjectName(QStringLiteral("renderingTab"));
        preferencesTabs->addTab(renderingTab, QString());

        verticalLayout->addWidget(preferencesTabs);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(PreferencesDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(PreferencesDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(PreferencesDialog);
        QObject::connect(okButton, SIGNAL(clicked()), PreferencesDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), PreferencesDialog, SLOT(reject()));

        preferencesTabs->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Dialog", Q_NULLPTR));
        preferencesTabs->setTabText(preferencesTabs->indexOf(inputTab), QApplication::translate("PreferencesDialog", "Input", Q_NULLPTR));
        preferencesTabs->setTabText(preferencesTabs->indexOf(renderingTab), QApplication::translate("PreferencesDialog", "Rendering", Q_NULLPTR));
        okButton->setText(QApplication::translate("PreferencesDialog", "OK", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("PreferencesDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H
