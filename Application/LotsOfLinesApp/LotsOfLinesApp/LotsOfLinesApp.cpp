#include "LotsOfLinesApp.h"
#include <QFileDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <QMetaType>
#include <QTableView>
#include "LoadDataDialog.h"
#include "PreferencesDialog.h"
#include "DataTableModel.h"
#include "LoadingWorker.h"
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

LotsOfLinesApp::LotsOfLinesApp(const QString& openFile, QWidget *parent)
	:QMainWindow(parent),
	m_dataSet(nullptr)
{
	ui.setupUi(this);

	//Setup rendering window
	auto rendererWidget = new VisualizationRendererWidget(this);

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

	// Register data types with meta system
	qRegisterMetaType<LotsOfLines::LoadOptions>("LotsOfLines::LoadOptions");
	qRegisterMetaType<std::shared_ptr<LotsOfLines::DataSet>>("std::shared_ptr<LotsOfLines::DataSet>");

	//Connect signals and slots
	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(onLoadFile()));
	connect(ui.actionPreferences, SIGNAL(triggered()), this, SLOT(onOpenPreferences()));

	//Open initial file
}

void LotsOfLinesApp::loadFile(const QString& filename, const LotsOfLines::LoadOptions& options)
{
	// Initialize progress dialog
	QProgressDialog progressDialog(this);
	progressDialog.setLabelText("Please wait while loading the data file. This may take awhile depending on the size.");
	progressDialog.setMaximum(100);
	// Initialize thread
	QThread *loadingThread = new QThread();
	// Initialize loader and progress messaging
	ProgressMessageCallback messenger(progressDialog);
	LotsOfLines::ProgressMessage *progress(&messenger);
	LoadingWorker *loader = new LoadingWorker(progress);
	loader->moveToThread(loadingThread);
	// Connect signals and slots
	connect(this, SIGNAL(requestDatasetUpdate(const QString&, const LotsOfLines::LoadOptions&)),
		loader, SLOT(updateDataset(const QString&, const LotsOfLines::LoadOptions&)));
	connect(loader, SIGNAL(datasetUpdated(std::shared_ptr<LotsOfLines::DataSet>)),
		this, SLOT(addNewDataset(std::shared_ptr<LotsOfLines::DataSet>)));
	connect(loader, SIGNAL(datasetUpdated(std::shared_ptr<LotsOfLines::DataSet>)), loadingThread, SLOT(quit()));
	connect(loadingThread, SIGNAL(finished()), &progressDialog, SLOT(reset()));
	connect(&progressDialog, SIGNAL(canceled()), loadingThread, SLOT(terminate()));
	// Start thread and emit request
	loadingThread->start();
	emit requestDatasetUpdate(filename, options);
	// Display dialog
	progressDialog.exec();
	// If load canceled, make sure to set nullptr dataset
	if (progressDialog.wasCanceled())
	{
		addNewDataset(nullptr);
	}
}

void LotsOfLinesApp::reloadDataTable()
{
	if (m_dataSet) {
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
}

void LotsOfLinesApp::addNewDataset(std::shared_ptr<LotsOfLines::DataSet> dataSet)
{
	m_dataSet = dataSet;
	if (m_dataSet == nullptr)
	{
		QMessageBox::warning(this, "Failed to load", "There was an error loading the data file.");
	}

	//Pass data along to rendering system
	for (auto rendererWidget : m_rendererWidgets)
	{
		auto renderingSystem = rendererWidget.second->getRenderingSystem();
		renderingSystem->setDataSet(m_dataSet);
		renderingSystem->redraw();
	}
	// Freezes with lots of classes
	reloadDataTable();
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

void LotsOfLinesApp::onOpenPreferences()
{
	PreferencesDialog dlg(this);
	dlg.exec();
}

void LotsOfLinesApp::onVisualizationChecked(int state)
{
	VisualizationTypeCheckbox* checkbox = (VisualizationTypeCheckbox*)sender();
	LotsOfLines::E_VISUALIZATION_TYPE visualizationType = checkbox->getVisualizationType();

	if (state)
	{
		//Init callback will be called by the rendering widget after OpenGL loads
		auto initCallback = [this, visualizationType](LotsOfLines::RenderingSystem* renderingSystem)
		{
			//Set visualization type and dataset now that OpenGL is initialized
			renderingSystem->setDataSet(m_dataSet);
			renderingSystem->setVisualizationType(visualizationType);
			renderingSystem->redraw();

			//Add options editor widget for visualization method
			OptionEditorWidget* editorWidget = new OptionEditorWidget(
				QString::fromStdString(renderingSystem->getCurrentVisualizationMethod()->getTypeName()),
				renderingSystem->getVisualizationOptions(),
				ui.optionsScrollArea
				);
			m_optionEditorWidgets[visualizationType] = editorWidget;
			ui.optionsScrollLayout->addWidget(editorWidget);

			//Connect option editing signal so that the visualization can be redrawn when options are changed
			connect(editorWidget, SIGNAL(optionChanged(const std::string&)), this, SLOT(onVisualizationOptionsChanged(const std::string&)));
		};

		//Create widget for screen section and use init callback to set parameters
		VisualizationRendererWidget* rendererWidget = new VisualizationRendererWidget(this, initCallback);
		m_rendererWidgets[checkbox->getVisualizationType()] = rendererWidget;
		reorderSplitScreens();
	}
	else
	{
		//Remove visualization type from splitscreen display
		m_rendererWidgets.erase(visualizationType);
		reorderSplitScreens();

		//Remove editor widget
		auto optionEditorWidget = m_optionEditorWidgets.find(visualizationType);
		if (optionEditorWidget != m_optionEditorWidgets.end())
		{
			ui.optionsScrollLayout->removeWidget(optionEditorWidget->second);
			delete optionEditorWidget->second;
			m_optionEditorWidgets.erase(optionEditorWidget);
		}
	}
}

void LotsOfLinesApp::onVisualizationOptionsChanged(const std::string& name)
{
	for (auto rendererWidget : m_rendererWidgets)
	{
		auto renderingSystem = rendererWidget.second->getRenderingSystem();
		renderingSystem->redraw();
	}
}

void LotsOfLinesApp::reorderSplitScreens()
{
	//Clear layout
	while (ui.centralLayout->count() > 0)
	{
		QLayoutItem* rendererLayoutItem = ui.centralLayout->itemAt(0);
		VisualizationRendererWidget* renderWidget = (VisualizationRendererWidget*)rendererLayoutItem->widget();
		LotsOfLines::E_VISUALIZATION_TYPE visualizationType = renderWidget->getRenderingSystem()->getCurrentVisualizationMethod()->getType();

		ui.centralLayout->removeItem(rendererLayoutItem);

		//If the visualization method has been disabled, then delete the rendering widget.
		if (m_rendererWidgets.find(visualizationType) == m_rendererWidgets.end())
		{
			delete renderWidget;
		}
	}

	//Assign based on index
	unsigned int idx = 0;
	for (auto widget : m_rendererWidgets)
	{
		unsigned int row = idx  / 2;
		unsigned int col = idx % 2;
		ui.centralLayout->addWidget(widget.second, row, col);

		idx++;
	}
}