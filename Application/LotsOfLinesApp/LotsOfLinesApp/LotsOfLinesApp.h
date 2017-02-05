#pragma once

#include <QMainWindow>
#include <LotsOfLines/DataModel.hpp>
#include "VisualizationRendererWidget.h"
#include "ui_LotsOfLinesApp.h"

class LotsOfLinesApp : public QMainWindow
{
    Q_OBJECT

public:

    LotsOfLinesApp(QWidget* parent = 0);

	///@brief Load a data set to be displayed.
	void loadFile(const QString& filename, const LotsOfLines::LoadOptions& options = LotsOfLines::LoadOptions::default);

public slots:

	void onLoadFile();
	void onVisualizationChecked(int state);

protected:

	///@brief Reloads the tabs and table models for the data table view.
	void reloadDataTable();

    Ui::LotsOfLinesAppClass ui;

	std::shared_ptr<LotsOfLines::DataSet> m_dataSet;

	VisualizationRendererWidget* m_rendererWidget;

	LotsOfLines::DataModel m_dataModel;
	LotsOfLines::RenderingSystem* m_renderingSystem;
};
