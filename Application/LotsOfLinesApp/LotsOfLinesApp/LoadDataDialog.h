#pragma once
#include <QDialog>
#include "ui_LoadDataDialog.h"

class LoadDataDialog : public QDialog, public Ui::Dialog
{
	Q_OBJECT

public:

	LoadDataDialog(QWidget* parent = 0);
};