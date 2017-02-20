#include <OptionEditorWidget.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

OptionEditorWidget::OptionEditorWidget(const QString& title, LotsOfLines::VisualizationOptions& options, QWidget* parent)
	:QGroupBox(title, parent),
	m_options(options),
	m_layout(this)
{
	const LotsOfLines::OptionTypeMap& optionList = options.listOptions();
	for (auto option : optionList)
	{
		//Create different widget depending on type of option
		QWidget* editorWidget = nullptr;
		//Booleans will be checkboxes
		if (option.second == LotsOfLines::EOT_BOOL)
		{
			editorWidget = new QCheckBox(QString::fromStdString(option.first), this);
			((QCheckBox*)editorWidget)->setChecked(options.getBool(option.first));
			connect(editorWidget, SIGNAL(stateChanged(int)), this, SLOT(onCheckboxChanged(int)));
		}
		else
		{
			m_layout.addWidget(new QLabel(QString::fromStdString(option.first), this));

			//String will be simply a line edit
			if (option.second == LotsOfLines::EOT_STRING)
			{
				editorWidget = new QLineEdit(this);
				((QLineEdit*)editorWidget)->setText(QString::fromStdString(options.getString(option.first)));
				connect(editorWidget, SIGNAL(textEdited(const QString&)), this, SLOT(onTextEdited(const QString&)));
			}
			//Both number types will be spinboxes
			else if (option.second == LotsOfLines::EOT_INTEGER)
			{
				editorWidget = new QSpinBox(this);
				((QSpinBox*)editorWidget)->setValue(options.getInt(option.first));
				connect(editorWidget, SIGNAL(valueChanged(int)), this, SLOT(onIntChanged(int)));
			}
			else if (option.second == LotsOfLines::EOT_DOUBLE)
			{
				editorWidget = new QDoubleSpinBox(this);
				((QDoubleSpinBox*)editorWidget)->setValue(options.getDouble(option.first));
				connect(editorWidget, SIGNAL(valueChanged(double)), this, SLOT(onDoubleChanged(double)));
			}
		}

		//Push to layout
		if (editorWidget)
		{
			editorWidget->setObjectName(QString::fromStdString(option.first));
			m_layout.addWidget(editorWidget);
		}
	}
}

void OptionEditorWidget::onCheckboxChanged(int state)
{
	QCheckBox* checkbox = (QCheckBox*)sender();
	m_options.setBool(checkbox->objectName().toStdString(), (bool)state);

	emit optionChanged(checkbox->objectName().toStdString());
}

void OptionEditorWidget::onTextEdited(const QString& text)
{
	QLineEdit* lineEdit = (QLineEdit*)sender();
	m_options.setString(lineEdit->objectName().toStdString(), text.toStdString());

	emit optionChanged(lineEdit->objectName().toStdString());
}

void OptionEditorWidget::onIntChanged(int n)
{
	QSpinBox* spinBox = (QSpinBox*)sender();
	m_options.setInt(spinBox->objectName().toStdString(), n);

	emit optionChanged(spinBox->objectName().toStdString());
}

void OptionEditorWidget::onDoubleChanged(double n)
{
	QDoubleSpinBox* spinBox = (QDoubleSpinBox*)sender();
	m_options.setDouble(spinBox->objectName().toStdString(), n);

	emit optionChanged(spinBox->objectName().toStdString());
}
