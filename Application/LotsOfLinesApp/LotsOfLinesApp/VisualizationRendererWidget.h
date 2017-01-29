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

	void mousePressEvent(QMouseEvent *eventPress);
	void mouseMoveEvent(QMouseEvent* eventMove);
	void mouseReleaseEvent(QMouseEvent *releaseEvent);
	void wheelEvent(QWheelEvent* wheelEvent);

protected:

	LotsOfLines::RenderingSystem m_renderingSystem;

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};