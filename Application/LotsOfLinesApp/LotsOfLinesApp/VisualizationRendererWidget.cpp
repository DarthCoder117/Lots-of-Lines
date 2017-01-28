#include <VisualizationRendererWidget.h>
#include <LotsOfLines/OpenGLRenderer.hpp>

VisualizationRendererWidget::VisualizationRendererWidget(QWidget* parent)
	:QOpenGLWidget(parent),
	m_renderingSystem(new LotsOfLines::OpenGLRenderer())
{

}

LotsOfLines::RenderingSystem* VisualizationRendererWidget::getRenderingSystem()
{
	return &m_renderingSystem;
}

void VisualizationRendererWidget::initializeGL()
{
	m_renderingSystem.init();
}

void VisualizationRendererWidget::resizeGL(int w, int h)
{
	m_renderingSystem.onResize((unsigned int)w, (unsigned int)h);
}

void VisualizationRendererWidget::paintGL()
{
	m_renderingSystem.beginDraw(0.5, 0.5, 0.5);

	m_renderingSystem.endDraw();
}
