#pragma once
#include <functional>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <LotsOfLines/RenderingSystem.hpp>

class VisualizationRendererWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:

	explicit VisualizationRendererWidget(QWidget* parent, std::function<void (LotsOfLines::RenderingSystem*)> initCallback = nullptr);

	LotsOfLines::RenderingSystem* getRenderingSystem();

	void mousePressEvent(QMouseEvent *eventPress);
	void mouseMoveEvent(QMouseEvent* eventMove);
	void mouseReleaseEvent(QMouseEvent *releaseEvent);
	void wheelEvent(QWheelEvent* wheelEvent);

protected:

	LotsOfLines::RenderingSystem m_renderingSystem;

	std::function<void(LotsOfLines::RenderingSystem*)> m_initCallback;

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};