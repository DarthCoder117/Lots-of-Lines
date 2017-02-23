#ifndef PREFERENCES_DIALOG_H
#define PREFERENCES_DIALOG_H
#include <QDialog>
#include <LotsOfLines/DataModel.hpp>
#include "ui_PreferencesDialog.h"

class PreferencesDialog : public QDialog, public Ui::PreferencesDialog
{
	Q_OBJECT

public:

	PreferencesDialog(QWidget* parent);
};

#endif
