#include <VisualizationRendererWidget.h>
#include <LotsOfLines/OpenGLRenderer.hpp>
#include <QMouseEvent>

VisualizationRendererWidget::VisualizationRendererWidget(QWidget* parent)
	:QOpenGLWidget(parent),
	m_renderingSystem(new LotsOfLines::OpenGLRenderer())
{

}

LotsOfLines::RenderingSystem* VisualizationRendererWidget::getRenderingSystem()
{
	return &m_renderingSystem;
}

void VisualizationRendererWidget::setDataSet(std::shared_ptr<LotsOfLines::DataSet> dataSet)
{
	m_dataSet = dataSet;
}

void VisualizationRendererWidget::setVisualizationMethod(LotsOfLines::E_VISUALIZATION_TYPE method)
{
	m_visualizationMethod = method;
}

LotsOfLines::E_VISUALIZATION_TYPE VisualizationRendererWidget::getVisualizationMethod()
{
	return m_visualizationMethod;
}

void VisualizationRendererWidget::mousePressEvent(QMouseEvent* eventMove)
{
	m_renderingSystem.onMousePress(eventMove->pos().x(), eventMove->pos().y());
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
	m_renderingSystem.setDataSet(m_dataSet);
	m_renderingSystem.setVisualizationType(m_visualizationMethod);
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
