#pragma once

#include <QtWidgets/QOpenGLWidget.h>

class VisualizationRendererWidget : public QOpenGLWidget
{
	Q_OBJECT

public:

	explicit VisualizationRendererWidget(QWidget* parent = 0);

protected:

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};