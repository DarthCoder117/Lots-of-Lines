#include "LotsOfLinesApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LotsOfLinesApp w;
    w.show();
    return a.exec();
}
