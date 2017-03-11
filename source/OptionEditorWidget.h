#ifndef OPTION_EDITOR_WIDGET_H
#define OPTION_EDITOR_WIDGET_H
#include <QGroupBox>
#include <QFormLayout>
#include <RenderingSystem/VisualizationOptions.hpp>

///@brief Widget for modifying generic options object.
class OptionEditorWidget : public QGroupBox
{
	Q_OBJECT

public:

	OptionEditorWidget(const QString& title, LotsOfLines::VisualizationOptions& options, QWidget* parent = 0);

	void* userPointer = nullptr;

public slots:

	void onCheckboxChanged(int state);
	void onTextEdited(const QString& text);
	void onIntChanged(int n);
	void onDoubleChanged(double n);

signals:
	
	///@brief Signal emitted when an option changes.
	void optionChanged(const std::string& name);

private:

	LotsOfLines::VisualizationOptions& m_options;
	QFormLayout m_layout;
};

#endif
