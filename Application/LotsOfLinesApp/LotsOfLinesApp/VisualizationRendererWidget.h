#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <LotsOfLines/RenderingSystem.hpp>

class VisualizationRendererWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:

	explicit VisualizationRendererWidget(QWidget* parent);

	LotsOfLines::RenderingSystem* getRenderingSystem();

	///@brief Set the data set that this rendering widget will use
	void setDataSet(std::shared_ptr<LotsOfLines::DataSet> dataSet);

	///@brief Set the visualization method used by this rendering widget.
	void setVisualizationMethod(LotsOfLines::E_VISUALIZATION_TYPE method);
	///@return The current visualization method used by this rendering widget.
	LotsOfLines::E_VISUALIZATION_TYPE getVisualizationMethod();

	void mousePressEvent(QMouseEvent *eventPress);
	void mouseMoveEvent(QMouseEvent* eventMove);
	void mouseReleaseEvent(QMouseEvent *releaseEvent);
	void wheelEvent(QWheelEvent* wheelEvent);

protected:

	LotsOfLines::RenderingSystem m_renderingSystem;

	std::shared_ptr<LotsOfLines::DataSet> m_dataSet;
	LotsOfLines::E_VISUALIZATION_TYPE m_visualizationMethod;

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};