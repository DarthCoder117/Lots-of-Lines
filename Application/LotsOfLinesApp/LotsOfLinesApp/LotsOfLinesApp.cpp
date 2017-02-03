#include "LotsOfLinesApp.h"
#include <QFileDialog>
#include <QCheckBox>
#include <QMessageBox>
#include "LoadDataDialog.h"
#include <LotsOfLines/RenderingSystem.hpp>
#include <LotsOfLines/IVisualizationMethod.hpp>

//Custom checkbox for selecting visualization methods.
class VisualizationTypeCheckbox : public QCheckBox
{
public:

	VisualizationTypeCheckbox(const QString& text, QWidget* parent, LotsOfLines::E_VISUALIZATION_TYPE type)
		:QCheckBox(text, parent),
		m_visualizationType(type)
	{}

	LotsOfLines::E_VISUALIZATION_TYPE getVisualizationType() { return m_visualizationType; }

private:

	LotsOfLines::E_VISUALIZATION_TYPE m_visualizationType;
};

LotsOfLinesApp::LotsOfLinesApp(QWidget *parent)
	:QMainWindow(parent),
	m_dataSet(nullptr),
	m_renderingSystem(nullptr)
{
	ui.setupUi(this);

	//Setup rendering window
	m_rendererWidget = new VisualizationRendererWidget(this);
	m_renderingSystem = m_rendererWidget->getRenderingSystem();
	ui.centralLayout->addWidget(m_rendererWidget);

	//Populate visualization type selection menu
	LotsOfLines::VisualizationMethodList visualizationMethods;
	m_renderingSystem->getVisualizationMethods(visualizationMethods);
	for (auto method : visualizationMethods)
	{
		VisualizationTypeCheckbox* methodCheckbox = new VisualizationTypeCheckbox(QString::fromStdString(method->getTypeName()), ui.visualizationTypeArea, method->getType());
		connect(methodCheckbox, SIGNAL(stateChanged(int)), this, SLOT(onVisualizationChecked(int)));
		ui.visualizationTypeLayout->addWidget(methodCheckbox);
	}

	//Setup dock widgets
	ui.menuView->addAction(ui.sidebarDockWidget->toggleViewAction());
	ui.menuView->addAction(ui.dataTableDock->toggleViewAction());

	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(onLoadFile()));
}

void LotsOfLinesApp::loadFile(const QString& filename, const LotsOfLines::LoadOptions& options)
{
	//Load data set through DataModel module.
	m_dataSet = m_dataModel.loadData(filename.toStdString(), options);
	if (m_dataSet == nullptr)
	{
		QMessageBox::warning(this, "Failed to load", "There was an error loading the data file.");
	}

	//Pass data along to rendering system
	m_renderingSystem->setDataSet(m_dataSet);
	//m_renderingSystem->enableVisualizationType(LotsOfLines::EVT_PARALLEL_COORDINATES);
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
		loadFile(file, options);
	}
}

void LotsOfLinesApp::onVisualizationChecked(int state)
{
	VisualizationTypeCheckbox* checkbox = (VisualizationTypeCheckbox*)sender();
	m_renderingSystem->enableVisualizationType(checkbox->getVisualizationType(), (bool)state);
}
