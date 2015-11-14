#include "blocktypesreader.h"

#include <QMap>
#include "flowchart/blocktype.h"
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "flowchart/datatype.h"

BlockTypesReader::BlockTypesReader() {}

QMap<QString, BlockType> BlockTypesReader::blockTypes() {
    return m_blockTypes;
}

void BlockTypesReader::read(QIODevice *device) {
    QByteArray bytes = device->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    QJsonObject node = doc.object();
    m_blockTypes = readBlockTypes(node["BlockTypes"]);
}

QMap<QString, BlockType> BlockTypesReader::readBlockTypes(QJsonValue node) {
    QJsonArray nodeArray = node.toArray();
    QMap<QString, BlockType> blockTypes;
    for (int i = 0; i < nodeArray.size(); i++) {
        QJsonValue element = nodeArray[i];
        BlockType bt = readBlockType(element);
        blockTypes[bt.name()] = bt;
    }
    return blockTypes;
}

BlockType BlockTypesReader::readBlockType(QJsonValue node) {
    QJsonObject nodeObject = node.toObject();
    QString name = nodeObject["name"].toString();
    QString displayName = nodeObject["displayName"].toString();
    QMap<QString, DataType> inputs = readPinList(nodeObject["inputs"]);
    QMap<QString, DataType> outputs = readPinList(nodeObject["outputs"]);
    BlockType blockType(name, displayName, inputs, outputs);
    return blockType;
}

QMap<QString, DataType> BlockTypesReader::readPinList(QJsonValue node) {
    QJsonObject nodeObject = node.toObject();
    QMap<QString, DataType> pinList;
    QJsonObject::const_iterator i;
    for (i = nodeObject.begin(); i != nodeObject.end(); i++) {
        pinList[i.key()] = static_cast<DataType>(i.value().toInt());
    }
    return pinList;
}
