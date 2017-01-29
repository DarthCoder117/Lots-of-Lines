#pragma once
#include <QDialog>
#include <LotsOfLines/DataModel.hpp>
#include "ui_LoadDataDialog.h"

class LoadDataDialog : public QDialog, public Ui::LoadDataDialog
{
	Q_OBJECT

public:

	LoadDataDialog(QWidget* parent, const QString& filePath);

	LotsOfLines::LoadOptions getLoadOptions();
};