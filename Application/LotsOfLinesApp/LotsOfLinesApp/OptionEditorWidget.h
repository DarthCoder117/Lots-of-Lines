#ifndef OPTION_EDITOR_WIDGET_H
#define OPTION_EDITOR_WIDGET_H
#include <QGroupBox>
#include <QFormLayout>
#include <LotsOfLines/VisualizationOptions.hpp>

///@brief Widget for modifying generic options object.
class OptionEditorWidget : public QGroupBox
{
	Q_OBJECT

public:

	OptionEditorWidget(const QString& title, LotsOfLines::VisualizationOptions& options, QWidget* parent = 0);

public slots:

	void onCheckboxChanged(int state);
	void onTextEdited(const QString& text);
	void onIntChanged(int n);
	void onDoubleChanged(double n);

private:

	LotsOfLines::VisualizationOptions& m_options;
	QFormLayout m_layout;
};

#endif