#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "applicationdata.h"
#include "blocktype.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonParseError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString appDir = a.applicationDirPath();

    QString xmlPath = appDir + "/blocks.json";
    QFile xmlFile(xmlPath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(0, "SignalCraft failed to open blocks.json",
                              "The block.json file could not be opened. Ensure that it exists.");
        return 1;
    }
    QByteArray bytes = xmlFile.readAll();
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &parseErr);
    if (parseErr.error != QJsonParseError::NoError) {
        QMessageBox::critical(0, "SignalCraft failed to parse blocks.json",
                              "The block.json file could not be parsed as valid JSON. The parser reported: \"" +
                              parseErr.errorString() +
                              "\" at offset " +
                              QString::number(parseErr.offset) +
                              ".");
        return 1;
    }
    QJsonArray nodeArray = doc.array();
    ApplicationData appData;
    bool success;
    appData.blockTypes = BlockTypes_fromJson(nodeArray, &success);
    if (!success) {
        QMessageBox::critical(0, "SignalCraft failed to interpret blocks.json",
                              "The block.json file did not fit the required structure.");
        return 1;
    }

    MainWindow w(appData);
    w.show();

    return a.exec();
}
