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

public slots:

	void onLoadFile();

protected:

	void initializeGL();
	void paintGL();

    Ui::LotsOfLinesAppClass ui;

	std::shared_ptr<LotsOfLines::DataSet> m_dataSet;

	VisualizationRendererWidget* m_rendererWidget;
};
