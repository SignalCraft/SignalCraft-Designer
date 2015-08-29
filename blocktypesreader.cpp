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

QVector<BlockType> BlockTypesReader::blockTypes() {
    return m_blockTypes;
}

void BlockTypesReader::read(QIODevice *device) {
    QByteArray bytes = device->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    QJsonObject node = doc.object();
    m_blockTypes = readBlockTypes(node["BlockTypes"]);
}

QVector<BlockType> BlockTypesReader::readBlockTypes(QJsonValue node) {
    QJsonArray nodeArray = node.toArray();
    QVector<BlockType> blockTypes(nodeArray.size());
    for (int i = 0; i < nodeArray.size(); i++) {
        QJsonValue element = nodeArray[i];
        blockTypes[i] = readBlockType(element);
    }
    return blockTypes;
}

BlockType BlockTypesReader::readBlockType(QJsonValue node) {
    QJsonObject nodeObject = node.toObject();
    BlockType blockType;
    blockType.name = nodeObject["name"].toString();
    blockType.inputs = readPinList(nodeObject["inputs"]);
    blockType.outputs = readPinList(nodeObject["outputs"]);
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
