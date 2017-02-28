#include "LoadDataDialog.h"

LoadDataDialog::LoadDataDialog(QWidget * parent, const QString& filePath) 
	:QDialog(parent) 
{
	setupUi(this);
	selectedFile->setText(filePath);
}

LotsOfLines::LoadOptions LoadDataDialog::getLoadOptions()
{
	LotsOfLines::LoadOptions options;
	
	options.dataNormalizationMode = (LotsOfLines::E_DATA_NORMALIZATION_MODE)normalizationMethodSelect->currentIndex();
	options.classColumn = classColumnSelect->value();
	
	return options;
}
