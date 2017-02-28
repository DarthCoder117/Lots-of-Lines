/********************************************************************************
** Form generated from reading UI file 'LoadDataDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADDATADIALOG_H
#define UI_LOADDATADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoadDataDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *selectedFile;
    QGroupBox *optionsGroupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *classColumnSelect;
    QLabel *label_2;
    QComboBox *normalizationMethodSelect;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *LoadDataDialog)
    {
        if (LoadDataDialog->objectName().isEmpty())
            LoadDataDialog->setObjectName(QStringLiteral("LoadDataDialog"));
        LoadDataDialog->resize(400, 153);
        verticalLayout = new QVBoxLayout(LoadDataDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        selectedFile = new QLineEdit(LoadDataDialog);
        selectedFile->setObjectName(QStringLiteral("selectedFile"));
        selectedFile->setEnabled(true);
        selectedFile->setReadOnly(true);

        verticalLayout->addWidget(selectedFile);

        optionsGroupBox = new QGroupBox(LoadDataDialog);
        optionsGroupBox->setObjectName(QStringLiteral("optionsGroupBox"));
        formLayout = new QFormLayout(optionsGroupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(optionsGroupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        classColumnSelect = new QSpinBox(optionsGroupBox);
        classColumnSelect->setObjectName(QStringLiteral("classColumnSelect"));

        formLayout->setWidget(1, QFormLayout::FieldRole, classColumnSelect);

        label_2 = new QLabel(optionsGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        normalizationMethodSelect = new QComboBox(optionsGroupBox);
        normalizationMethodSelect->setObjectName(QStringLiteral("normalizationMethodSelect"));

        formLayout->setWidget(0, QFormLayout::FieldRole, normalizationMethodSelect);


        verticalLayout->addWidget(optionsGroupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cancelButton = new QPushButton(LoadDataDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);

        okButton = new QPushButton(LoadDataDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout_2->addWidget(okButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(LoadDataDialog);
        QObject::connect(cancelButton, SIGNAL(clicked()), LoadDataDialog, SLOT(reject()));
        QObject::connect(okButton, SIGNAL(clicked()), LoadDataDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(LoadDataDialog);
    } // setupUi

    void retranslateUi(QDialog *LoadDataDialog)
    {
        LoadDataDialog->setWindowTitle(QApplication::translate("LoadDataDialog", "Load Data", Q_NULLPTR));
        optionsGroupBox->setTitle(QApplication::translate("LoadDataDialog", "Options", Q_NULLPTR));
        label->setText(QApplication::translate("LoadDataDialog", "Class Column", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        classColumnSelect->setToolTip(QApplication::translate("LoadDataDialog", "The column index that will be used as the data class.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("LoadDataDialog", "Normalization Method", Q_NULLPTR));
        normalizationMethodSelect->clear();
        normalizationMethodSelect->insertItems(0, QStringList()
         << QApplication::translate("LoadDataDialog", "no normalization", Q_NULLPTR)
         << QApplication::translate("LoadDataDialog", "per variable", Q_NULLPTR)
         << QApplication::translate("LoadDataDialog", "global min/max", Q_NULLPTR)
         << QApplication::translate("LoadDataDialog", "per class", Q_NULLPTR)
        );
        cancelButton->setText(QApplication::translate("LoadDataDialog", "Cancel", Q_NULLPTR));
        okButton->setText(QApplication::translate("LoadDataDialog", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoadDataDialog: public Ui_LoadDataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADDATADIALOG_H
