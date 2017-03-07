#include "LoadDataDialog.h"

LoadDataDialog::LoadDataDialog(QWidget * parent, const QString& filePath) 
	:QDialog(parent) 
{
	setupUi(this);
	selectedFile->setText(filePath);

	connect(customClassColumnCheckbox, SIGNAL(stateChanged(int)), this, SLOT(customClassChecked(int)));
}

LotsOfLines::LoadOptions LoadDataDialog::getLoadOptions()
{
	LotsOfLines::LoadOptions options;
	
	options.dataNormalizationMode = (LotsOfLines::E_DATA_NORMALIZATION_MODE)normalizationMethodSelect->currentIndex();
	options.classColumn = classColumnSelect->value();
	options.customClassColumn = customClassColumnCheckbox->isChecked();
	
	return options;
}

void LoadDataDialog::customClassChecked(int state)
{
	classColumnSelect->setEnabled(customClassColumnCheckbox->checkState() == Qt::Checked);
}