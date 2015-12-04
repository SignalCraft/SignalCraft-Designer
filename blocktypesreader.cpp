#include "blocktypesreader.h"

#include <QMap>
#include "flowchart/blocktype.h"
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "flowchart/datatype.h"
#include "flowchart/blockoption.h"
#include "flowchart/blockoptioninteger.h"
#include "flowchart/blockoptioncombobox.h"
#include <QSharedPointer>
#include <QMap>

BlockTypesReader::BlockTypesReader() {}

QMap<QString, BlockType> BlockTypesReader::blockTypes() const {
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
    QMap<QString, QSharedPointer<const BlockOption> > options;
    QJsonObject optionsNodeObject = nodeObject["options"].toObject();
    for (QJsonObject::const_iterator i = optionsNodeObject.begin(); i != optionsNodeObject.end(); i++) {
        options[i.key()] = readBlockOption(i.value());
    }
    BlockType blockType(name, displayName, inputs, outputs, options);
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

QSharedPointer<const BlockOption> BlockTypesReader::readBlockOption(QJsonValue node) {
    QJsonObject nodeObject = node.toObject();
    QString displayName = nodeObject["displayName"].toString();
    QString defaultValue = nodeObject["defaultValue"].toString();
    QString optionType = nodeObject["optionType"].toString();
    if (optionType == "integer") {
        int minimum = 0;
        int maximum = 99;
        QJsonValue minimumMaybe = nodeObject["minimum"];
        if (!(minimumMaybe.isNull() || minimumMaybe.isUndefined())) {
            minimum = minimumMaybe.toInt();
        }
        QJsonValue maximumMaybe = nodeObject["maximum"];
        if (!(maximumMaybe.isNull() || minimumMaybe.isUndefined())) {
            maximum = maximumMaybe.toInt();
        }
        return QSharedPointer<const BlockOption>(new BlockOptionInteger(displayName, defaultValue, minimum, maximum));
    } else if (optionType == "combobox") {
        QJsonObject choicesNodeObject = nodeObject["choices"].toObject();
        QMap<QString, QString> choices;
        for (QJsonObject::const_iterator i = choicesNodeObject.begin(); i != choicesNodeObject.end(); i++) {
            choices[i.key()] = i.value().toString();
        }
        return QSharedPointer<const BlockOption>(new BlockOptionComboBox(displayName, defaultValue, choices));
    } else if (optionType == "float") {
        // TODO: throw
        throw "abc";
    } else if (optionType == "stringInput") {
        // TODO: throw
        throw "abc";
    } else {
        // TODO: throw
        throw "abc";
    }
}
