#include <VisualizationRendererWidget.h>
#include <LotsOfLines/OpenGLRenderer.hpp>
#include <QMouseEvent>

VisualizationRendererWidget::VisualizationRendererWidget(QWidget* parent, std::function<void(LotsOfLines::RenderingSystem*)> initCallback)
	:QOpenGLWidget(parent),
	m_renderingSystem(new LotsOfLines::OpenGLRenderer()),
	m_initCallback(initCallback)
{
	QSurfaceFormat format;
	format.setMajorVersion(3);
	format.setMinorVersion(3);
	format.setProfile(QSurfaceFormat::CompatibilityProfile);
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setSamples(8);
	setFormat(format);
}

LotsOfLines::RenderingSystem* VisualizationRendererWidget::getRenderingSystem()
{
	return &m_renderingSystem;
}

void VisualizationRendererWidget::mousePressEvent(QMouseEvent* eventMove)
{
	bool lmb = eventMove->buttons().testFlag(Qt::LeftButton);
	bool rmb = eventMove->buttons().testFlag(Qt::RightButton);
	m_renderingSystem.onMousePress(eventMove->pos().x(), eventMove->pos().y(), lmb, rmb);
}

void VisualizationRendererWidget::mouseMoveEvent(QMouseEvent* eventMove)
{
	bool lmb = eventMove->buttons().testFlag(Qt::LeftButton);
	bool rmb = eventMove->buttons().testFlag(Qt::RightButton);
	m_renderingSystem.onMouseMove(eventMove->pos().x(), eventMove->pos().y(), lmb, rmb);
}

void VisualizationRendererWidget::mouseReleaseEvent(QMouseEvent* eventMove)
{
	bool lmb = eventMove->buttons().testFlag(Qt::LeftButton);
	bool rmb = eventMove->buttons().testFlag(Qt::RightButton);
	m_renderingSystem.onMouseRelease(eventMove->pos().x(), eventMove->pos().y(), lmb, rmb);
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
