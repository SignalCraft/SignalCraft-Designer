#include "blocktype.h"

#include <QtGlobal>
#include <QPointF>
#include <QString>
#include "blockoption.h"
#include "jsonforqt.h"
#include "pintype.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QHash>
#include "overloadtype.h"
#include "lisp_exp.h"

BlockType::BlockType() {
    m_name = "";
}

BlockType::BlockType(QString name, QString displayName, OverloadType overloadType, QMap<QString, PinType> inputs, QMap<QString, PinType> outputs, QMap<QString, BlockOption> options, QMap<QString, PinType> storage, lisp_exp parseTree) {
    m_name = name;
    m_displayName = displayName;
    m_overloadType = overloadType;
    m_inputs = inputs;
    m_outputs = outputs;
    m_options = options;
    m_storage = storage;
    m_parseTree = parseTree;
}

bool BlockType::isValid() const {
    return !m_name.isEmpty();
}

QPointF BlockType::inputPinPos(QString pinName) const {
    int pinIndex = 0;
    for (auto inputPin : inputs().keys()) {
        if (inputPin == pinName) {
            break;
        }
        pinIndex++;
    }
    return inputPinIndexToPos(pinIndex);
}

QPointF BlockType::outputPinPos(QString pinName) const {
    int pinIndex = 0;
    for (auto outputPin : outputs().keys()) {
        if (outputPin == pinName) {
            break;
        }
        pinIndex++;
    }
    return outputPinIndexToPos(pinIndex);
}

QPointF BlockType::inputPinCenterPos(QString pinName) const {
    return inputPinPos(pinName) + QPointF(100, 50);
}

QPointF BlockType::outputPinCenterPos(QString pinName) const {
    return outputPinPos(pinName) + QPointF(100, 50);
}

qreal BlockType::displayWidth() const {
    return 400;
}

qreal BlockType::displayHeight() const {
    return 100*(1+std::max(inputs().size(), outputs().size()));
}

bool BlockType::isPinOutput(QString pinName) const {
    return outputs().contains(pinName);
}


QString BlockType::name() const {
    return m_name;
}

QString BlockType::displayName() const {
    return m_displayName;
}

OverloadType BlockType::overloadType() const {
    return m_overloadType;
}

QMap<QString, PinType> BlockType::inputs() const {
    return m_inputs;
}

QMap<QString, PinType> BlockType::outputs() const {
    return m_outputs;
}

QMap<QString, BlockOption> BlockType::options() const {
    return m_options;
}

QMap<QString, PinType> BlockType::storage() const {
    return m_storage;
}

lisp_exp BlockType::parseTree() const {
    return m_parseTree;
}

QHash<QString, QString> BlockType::defaultOptionValues() const {
    QHash<QString, QString> defaults;
    for (QString optionName : options().keys()) {
        BlockOption option = options()[optionName];
        defaults[optionName] = option.defaultValue();
    }
    return defaults;
}

QHash<QString, QString> BlockType::resultingOptionValues(QHash<QString, QString> optionValues) const {
    for (QString optionName : options().keys()) {
        if (!optionValues.contains(optionName)) {
            optionValues.insert(optionName, options().value(optionName).defaultValue());
        }
    }
    return optionValues;
}

QPointF BlockType::inputPinIndexToPos(int pinIndex) {
    return QPointF(0, 100*(1+pinIndex));
}

QPointF BlockType::outputPinIndexToPos(int pinIndex) {
    return QPointF(200, 100*(1+pinIndex));
}

QPointF BlockType::inputPinIndexToCenterPos(int pinIndex) {
    return inputPinIndexToPos(pinIndex) + QPointF(100, 50);
}

QPointF BlockType::outputPinIndexToCenterPos(int pinIndex) {
    return outputPinIndexToPos(pinIndex) + QPointF(100, 50);
}

QJsonValue BlockType_toJson(BlockType obj) {
    QJsonObject nodeObj;
    nodeObj["name"] = obj.name();
    nodeObj["displayName"] = obj.displayName();
    nodeObj["overloadType"] = OverloadType_toJson(obj.overloadType());
    nodeObj["inputs"] = QMap_QString_PinType_toJson(obj.inputs());
    nodeObj["outputs"] = QMap_QString_PinType_toJson(obj.outputs());
    nodeObj["options"] = QMap_QString_BlockOption_toJson(obj.options());
    nodeObj["storage"] = QMap_QString_PinType_toJson(obj.storage());
    // TODO: storing parseTree requires lisp_exp.toString()
    return nodeObj;
}

BlockType BlockType_fromJson(QJsonValue node) {
    QJsonObject nodeObj = node.toObject();
    QString name = nodeObj["name"].toString();
    QString displayName = nodeObj["displayName"].toString();
    OverloadType overloadType = OverloadType_fromJson(nodeObj["overloadType"]);
    QMap<QString, PinType> inputs = QMap_QString_PinType_fromJson(nodeObj["inputs"]);
    QMap<QString, PinType> outputs = QMap_QString_PinType_fromJson(nodeObj["outputs"]);
    QMap<QString, BlockOption> options = QMap_QString_BlockOption_fromJson(nodeObj["options"]);
    QMap<QString, PinType> storage = QMap_QString_PinType_fromJson(nodeObj["storage"]);
    lisp_exp parseTree = lisp_exp::parseString(nodeObj["parseTree"].toString());
    return BlockType(name, displayName, overloadType, inputs, outputs, options, storage, parseTree);
}

QJsonValue BlockTypes_toJson(QHash<QString, BlockType> obj) {
    QJsonArray nodeArray;
    for (BlockType bt : obj) {
        nodeArray.append(BlockType_toJson(bt));
    }
    return nodeArray;
}

QHash<QString, BlockType> BlockTypes_fromJson(QJsonValue node) {
    QJsonArray nodeArray = node.toArray();
    QHash<QString, BlockType> blockTypes;
    for (int i = 0; i < nodeArray.size(); i++) {
        QJsonValue element = nodeArray[i];
        BlockType bt = BlockType_fromJson(element);
        blockTypes[bt.name()] = bt;

    }
    return blockTypes;
}
