#include "LotsOfLinesApp.h"
#include <QFileDialog>
#include <QMessageBox>
#include "LoadDataDialog.h"

LotsOfLinesApp::LotsOfLinesApp(QWidget *parent)
	:QMainWindow(parent),
	m_dataSet(nullptr)
{
	ui.setupUi(this);

	//Setup rendering window
	m_rendererWidget = new VisualizationRendererWidget(this);
	ui.centralLayout->addWidget(m_rendererWidget);

	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(onLoadFile()));
}

void LotsOfLinesApp::onLoadFile()
{
	//Get file path of data to load
	QString file = QFileDialog::getOpenFileName(this, "Select data file");
	if (file.isNull())
	{
		return;
	}
	
	//Show data loading options
	LoadDataDialog dlg(this, file);
	if (dlg.exec() == QDialog::Accepted)
	{
		LotsOfLines::LoadOptions options = dlg.getLoadOptions();

		LotsOfLines::DataModel dataModel;
		m_dataSet = dataModel.loadData(file.toStdString(), options);
		if (m_dataSet == nullptr)
		{
			QMessageBox::warning(this, "Failed to load", "There was an error loading the data file.");
		}

		m_rendererWidget->getRenderingSystem()->setDataSet(m_dataSet);
		m_rendererWidget->getRenderingSystem()->setVisualizationType(LotsOfLines::EVT_PARALLEL_COORDINATES);
	}
}
