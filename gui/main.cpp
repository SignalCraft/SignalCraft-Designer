#include "gui/mainwindow.h"
#include <QApplication>
#include <QFile>
#include "gui/applicationdata.h"
#include "flowchart/blocktype.h"
#include <QJsonDocument>
#include <QJsonArray>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString appDir = a.applicationDirPath();

    QString xmlPath = appDir + "/blocks.json";
    QFile xmlFile(xmlPath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error message
        return 1;
    }
    QByteArray bytes = xmlFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    QJsonArray nodeArray = doc.array();
    ApplicationData appData;
    appData.blockTypes = BlockTypes_fromJson(nodeArray);

    MainWindow w(appData);
    w.show();

    return a.exec();
}
