#ifndef LOAD_DATA_DIALOG_H
#define LOAD_DATA_DIALOG_H
#include <QDialog>
#include <LotsOfLines/DataModel.hpp>
#include "ui_LoadDataDialog.h"

class LoadDataDialog : public QDialog, public Ui::LoadDataDialog
{
	Q_OBJECT

public:

	LoadDataDialog(QWidget* parent, const QString& filePath);

	LotsOfLines::LoadOptions getLoadOptions();

public slots:

	void customClassChecked(int state);
};

#endif