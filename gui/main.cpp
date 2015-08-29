#include "gui/mainwindow.h"
#include <QApplication>
#include <QFile>
#include "blocktypesreader.h"
#include "gui/applicationdata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString appDir = a.applicationDirPath();

    QString xmlPath = appDir + "/blocks.xml";
    QFile xmlFile(xmlPath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error message
        return 1;
    }
    BlockTypesReader reader;
    reader.read(&xmlFile);
    ApplicationData appData;
    appData.blockTypes = reader.blockTypes();

    MainWindow w(appData);
    w.show();

    return a.exec();
}
