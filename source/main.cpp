#include "LotsOfLinesApp.h"
#include <QtWidgets/QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	app.setApplicationName("Lots of Lines");

    //Setup command line options
	QCommandLineParser parser;
	parser.addPositionalArgument("file", "Data file to open");

    QCommandLineOption parallelCoordinatesOption("p", "parallel coordinates");
    parser.addOption(parallelCoordinatesOption);
    QCommandLineOption collocatedPairedOption("c", "collocated paired coordinates");
    parser.addOption(collocatedPairedOption);
    QCommandLineOption radialPairedOption("r", "radial (anchored) paired coordinates");
    parser.addOption(radialPairedOption);
    QCommandLineOption shiftedPairedOption("s", "shifted paired coordinates");
    parser.addOption(shiftedPairedOption);

    //Parse the selected options
    parser.process(app);
    const QStringList args = parser.positionalArguments();

    //Start application with selected options.
    LotsOfLinesApp w(args.count() >= 1 ? args.at(0) : "", parser.isSet(parallelCoordinatesOption), parser.isSet(collocatedPairedOption), parser.isSet(radialPairedOption), parser.isSet(shiftedPairedOption));
    w.show();
    return app.exec();
}
