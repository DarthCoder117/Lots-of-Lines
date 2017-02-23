#pragma once

#include <QMainWindow>
#include <LotsOfLines/DataModel.hpp>
#include "VisualizationRendererWidget.h"
#include "OptionEditorWidget.h"
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
	void onOpenPreferences();
	void onVisualizationChecked(int state);
	void onVisualizationOptionsChanged(const std::string& name);

protected:

	///@brief Reloads the tabs and table models for the data table view.
	void reloadDataTable();
	///@brief Reorder the positions of each screen in the splitscreen layout.
	///This must be called whenever the splitscreen widgets change, or else holes can appear in the layout.
	void reorderSplitScreens();

    Ui::LotsOfLinesAppClass ui;

	std::shared_ptr<LotsOfLines::DataSet> m_dataSet;

	LotsOfLines::DataModel m_dataModel;

	std::map<LotsOfLines::E_VISUALIZATION_TYPE, VisualizationRendererWidget*> m_rendererWidgets;
	std::map<LotsOfLines::E_VISUALIZATION_TYPE, OptionEditorWidget*> m_optionEditorWidgets;
};
