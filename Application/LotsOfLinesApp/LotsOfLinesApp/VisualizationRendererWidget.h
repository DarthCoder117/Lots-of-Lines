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

protected:

	LotsOfLines::RenderingSystem m_renderingSystem;

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};