#pragma once

#include <QMainWindow>
#include <QtWidgets/qprogressdialog.h>
#include <LotsOfLines/DataModel.hpp>
#include <LotsOfLines/DataSet.hpp>
#include <LotsOfLines/ProgressMessage.hpp>
#include "VisualizationRendererWidget.h"
#include "OptionEditorWidget.h"
#include "ui_LotsOfLinesApp.h"

class ProgressMessageCallback : public QObject, public LotsOfLines::ProgressMessage
{
	Q_OBJECT
public:
	ProgressMessageCallback(QProgressDialog &gui) : QObject(), LotsOfLines::ProgressMessage()
	{
		connect(this, SIGNAL(progressSignal(const int &)), &gui, SLOT(setValue(const int &)), Qt::QueuedConnection);
	}
	virtual void progress(int p)
	{
		emit progressSignal(p);
	}

signals:
	void progressSignal(const int &p);
};

class LotsOfLinesApp : public QMainWindow
{
    Q_OBJECT

public:

    LotsOfLinesApp(const QString& openFile, QWidget* parent = 0);

	///@brief Load a data set to be displayed.
	void loadFile(const QString& filename, const LotsOfLines::LoadOptions& options = LotsOfLines::LoadOptions::default);

public slots:

	void addNewDataset(std::shared_ptr<LotsOfLines::DataSet>);
	void onLoadFile();
	void onOpenPreferences();
	void onVisualizationChecked(int state);
	void onVisualizationOptionsChanged(const std::string& name);

signals:
	void requestDatasetUpdate(const QString& filename, const LotsOfLines::LoadOptions& options = LotsOfLines::LoadOptions::default);

protected:

	///@brief Reloads the tabs and table models for the data table view.
	void reloadDataTable();
	///@brief Reorder the positions of each screen in the splitscreen layout.
	///This must be called whenever the splitscreen widgets change, or else holes can appear in the layout.
	void reorderSplitScreens();

    Ui::LotsOfLinesAppClass ui;

	std::shared_ptr<LotsOfLines::DataSet> m_dataSet;

	std::map<LotsOfLines::E_VISUALIZATION_TYPE, VisualizationRendererWidget*> m_rendererWidgets;
	std::map<LotsOfLines::E_VISUALIZATION_TYPE, OptionEditorWidget*> m_optionEditorWidgets;
};
