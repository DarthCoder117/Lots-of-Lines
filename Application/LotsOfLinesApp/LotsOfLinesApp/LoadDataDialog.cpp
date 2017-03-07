#include "LoadDataDialog.h"
#include <sstream>

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
	
    std::istringstream is(ignoredColumnsLineEdit->text().toStdString());
	std::string column;
	
	while (std::getline(is, column, ',')) {
		try
		{
			unsigned int col = std::stoi(column);
			options.ignoreColumns.push_back(col);
		}
		catch (std::invalid_argument e)
		{
			// Invalid column
		}
		catch (std::out_of_range e)
		{
			// e.what
		}
	}
	
	return options;
}

void LoadDataDialog::customClassChecked(int state)
{
	classColumnSelect->setEnabled(customClassColumnCheckbox->checkState() == Qt::Checked);
}
