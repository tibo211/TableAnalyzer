#include "tableanalyzerwindow.h"
#include <QApplication>
#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TableAnalyzerWindow w;
    w.show();

    return a.exec();
}
