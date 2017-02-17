#include "LotsOfLinesApp.h"
#include <QFileDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <QTableView>
#include "LoadDataDialog.h"
#include "DataTableModel.h"
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
	m_dataSet(nullptr)
{
	ui.setupUi(this);

	//Setup rendering window
	auto rendererWidget = new VisualizationRendererWidget(this);
	//m_renderingSystem = m_rendererWidget->getRenderingSystem();
	//ui.centralLayout->addWidget(m_rendererWidget);

	//Populate visualization type selection menu
	LotsOfLines::VisualizationMethodList visualizationMethods;
	rendererWidget->getRenderingSystem()->getVisualizationMethods(visualizationMethods);
	for (auto method : visualizationMethods)
	{
		VisualizationTypeCheckbox* methodCheckbox = new VisualizationTypeCheckbox(QString::fromStdString(method->getTypeName()), ui.visualizationTypeArea, method->getType());
		connect(methodCheckbox, SIGNAL(stateChanged(int)), this, SLOT(onVisualizationChecked(int)));
		ui.visualizationTypeLayout->addWidget(methodCheckbox);
	}

	delete rendererWidget;

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
	for (auto rendererWidget : m_rendererWidgets)
	{
		rendererWidget.second->getRenderingSystem()->setDataSet(m_dataSet);
	}

	reloadDataTable();
}

void LotsOfLinesApp::reloadDataTable()
{
	//Delete all tabs
	for (unsigned int i = 0; i < ui.dataClassTabs->count(); ++i)
	{
		QWidget* tab = ui.dataClassTabs->widget(i);
		delete tab;
	}
	ui.dataClassTabs->clear();

	//Generate new tabs for each data class
	for (auto dataClass : m_dataSet->getClasses())
	{
		QTableView* dataTable = new QTableView(ui.dataClassTabs);
		dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		dataTable->setModel(new DataTableModel(m_dataSet, dataClass));
		dataTable->setSelectionMode(QAbstractItemView::NoSelection);

		ui.dataClassTabs->addTab(dataTable, QString::fromStdString(dataClass));
	}
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

	if (state)
	{
		VisualizationRendererWidget* rendererWidget = new VisualizationRendererWidget(this);
		rendererWidget->setDataSet(m_dataSet);
		rendererWidget->setVisualizationMethod(checkbox->getVisualizationType());

		m_rendererWidgets[checkbox->getVisualizationType()] = rendererWidget;

		unsigned int numSplitScreens = m_rendererWidgets.size();
		unsigned int row = (numSplitScreens - 1) / 2;
		unsigned int col = (numSplitScreens - 1) % 2;
		ui.centralLayout->addWidget(rendererWidget, row, col);
	}
	else
	{
		for (unsigned int i = 0; i < ui.centralLayout->count(); ++i)
		{
			QLayoutItem* rendererLayoutItem = ui.centralLayout->itemAt(i);
			VisualizationRendererWidget* renderWidget = (VisualizationRendererWidget*)rendererLayoutItem->widget();
			if (renderWidget->getVisualizationMethod() == checkbox->getVisualizationType())
			{
				m_rendererWidgets.erase(checkbox->getVisualizationType())
				ui.centralLayout->removeItem(rendererLayoutItem);
				delete renderWidget;
			}
		}
	}

	
}
