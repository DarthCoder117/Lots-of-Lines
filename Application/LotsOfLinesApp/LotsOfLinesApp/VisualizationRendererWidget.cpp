#include <VisualizationRendererWidget.h>
#include <LotsOfLines/OpenGLRenderer.hpp>
#include <QMouseEvent>

VisualizationRendererWidget::VisualizationRendererWidget(QWidget* parent, std::function<void(LotsOfLines::RenderingSystem*)> initCallback)
	:QOpenGLWidget(parent),
	m_renderingSystem(new LotsOfLines::OpenGLRenderer()),
	m_initCallback(initCallback)
{

}

LotsOfLines::RenderingSystem* VisualizationRendererWidget::getRenderingSystem()
{
	return &m_renderingSystem;
}

void VisualizationRendererWidget::mousePressEvent(QMouseEvent* eventMove)
{
	if (eventMove->button() == Qt::LeftButton)
	{
		m_renderingSystem.onMousePress(eventMove->pos().x(), eventMove->pos().y());
	}
	else if (eventMove->button() == Qt::RightButton)
	{
		m_renderingSystem.onRightClick(eventMove->pos().x(), eventMove->pos().y());
	}
}

void VisualizationRendererWidget::mouseMoveEvent(QMouseEvent* eventMove)
{
	m_renderingSystem.onMouseMove(eventMove->pos().x(), eventMove->pos().y());
}

void VisualizationRendererWidget::mouseReleaseEvent(QMouseEvent* eventMove)
{
	m_renderingSystem.onMouseRelease(eventMove->pos().x(), eventMove->pos().y());
}

void VisualizationRendererWidget::wheelEvent(QWheelEvent* wheelEvent)
{
	m_renderingSystem.onMouseScroll(wheelEvent->delta() / 8);
}

void VisualizationRendererWidget::initializeGL()
{
	m_renderingSystem.init();

	if (m_initCallback)
	{
		m_initCallback(&m_renderingSystem);
	}
}

void VisualizationRendererWidget::resizeGL(int w, int h)
{
	m_renderingSystem.onResize((unsigned int)w, (unsigned int)h);
}

void VisualizationRendererWidget::paintGL()
{
	m_renderingSystem.draw();

	update();
}
