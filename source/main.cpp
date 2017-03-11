#include "LotsOfLinesApp.h"
#include <QtWidgets/QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	app.setApplicationName("Lots of Lines");

	QCommandLineParser parser;
	parser.addPositionalArgument("file", "Data file to open");

	const QStringList args = parser.positionalArguments();

    LotsOfLinesApp w(!args.isEmpty() ? args.at(0) : "");
    w.show();
    return app.exec();
}
