#include "LotsOfLinesApp.h"
#include "LoadDataDialog.h"

LotsOfLinesApp::LotsOfLinesApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(onLoadFile()));
}

void LotsOfLinesApp::onLoadFile()
{
	LoadDataDialog* dlg = new LoadDataDialog(this);
	dlg->show();
}
