#include "block.h"

#include <QString>
#include <QPointF>
#include "blockpin.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include "jsonforqt.h"

Block::Block() {
    m_blockTypeName = "";
}

Block::Block(QString blockTypeName, QPointF pos) {
    m_blockTypeName = blockTypeName;
    m_pos = pos;
}

Block::Block(QString blockTypeName, QPointF pos, QHash<QString, BlockPin> inputConnections, QHash< QString, QSet< BlockPin > > outputConnections) : Block(blockTypeName, pos) {
    m_inputConnections = inputConnections;
    m_outputConnections = outputConnections;
}

bool Block::isValid() const {
    return !m_blockTypeName.isEmpty();
}

void Block::connectOutput(QString outputPinName, BlockPin inputPin) {
    m_outputConnections[outputPinName].insert(inputPin);
}

void Block::disconnectOutput(QString outputPinName, BlockPin inputPin) {
    m_outputConnections[outputPinName].remove(inputPin);
}

void Block::connectInput(QString inputPinName, BlockPin outputPin) {
    m_inputConnections.insert(inputPinName,outputPin);
}

void Block::disconnectInput(QString inputPinName) {
    m_inputConnections.remove(inputPinName);
}

void Block::setPos(QPointF pos) {
    m_pos = pos;
}

void Block::setOptionValue(QString optionName, QString value) {
    m_optionValues.insert(optionName, value);
}

void Block::resetOptionValues() {
    m_optionValues = QHash<QString, QString>();
}

QPointF Block::pos() const {
    return m_pos;
}

QString Block::blockTypeName() const {
    return m_blockTypeName;
}

bool Block::hasInputConnections() const {
    return !m_inputConnections.isEmpty();
}

BlockPin Block::inputConnection(QString inputPinName) const {
    return m_inputConnections.value(inputPinName);
}

QSet<BlockPin> Block::outputConnection(QString outputPinName) const {
    return m_outputConnections.value(outputPinName);
}

QString Block::optionValue(QString optionName) const {
    return m_optionValues.value(optionName);
}

QString Block::optionValue(QString optionName, QString defaultValue) const {
    return m_optionValues.value(optionName, defaultValue);
}

QJsonValue Block::toJson() const {
    QJsonObject nodeObj;
    nodeObj["blockTypeName"] = m_blockTypeName;
    nodeObj["pos"] = QPointF_toJson(m_pos);
    nodeObj["inputConnections"] = QHash_QString_BlockPin_toJson(m_inputConnections);
    nodeObj["outputConnections"] = QHash_QString_QSet_BlockPin_toJson(m_outputConnections);
    return nodeObj;
}

QJsonValue Block_toJson(Block obj) {
    return obj.toJson();
}

Block Block_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QJsonObject nodeObj = node.toObject();
    if (nodeObj.isEmpty()) {
        success = false;
    }
    QJsonValue blockTypeNameVal = nodeObj["blockTypeName"];
    if (!blockTypeNameVal.isString()) {
        success = false;
    }
    QPointF pos = QPointF_fromJson(nodeObj["pos"], &callSuccess);
    if (!callSuccess) {
        success = false;
    }
    QHash<QString, BlockPin> inputConnections = QHash_QString_BlockPin_fromJson(nodeObj["inputConnections"], &callSuccess);
    if (!callSuccess) {
        success = false;
    }
    QHash<QString, QSet<BlockPin>> outputConnections = QHash_QString_QSet_BlockPin_fromJson(nodeObj["outputConnections"], &callSuccess);
    if (!callSuccess) {
        success = false;
    }
    if (ok) {
        *ok = success;
    }
    return Block(blockTypeNameVal.toString(), pos, inputConnections, outputConnections);
}

QJsonValue QHash_int_Block_toJson(QHash<int, Block> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = Block_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QHash<int, Block> QHash_int_Block_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QHash<int, Block> obj;
    if (!node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QJsonValue keyVal = item["key"];
        if (!keyVal.isDouble() || (keyVal.toInt() != keyVal.toDouble())) {
            success = false;
        }
        int key = keyVal.toInt();
        Block value = Block_fromJson(item["value"], &callSuccess);
        if (!callSuccess) {
            success = false;
        }
        obj.insert(key, value);
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}

QJsonValue QMap_int_Block_toJson(QMap<int, Block> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = Block_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QMap<int, Block> QMap_int_Block_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QMap<int, Block> obj;
    if (!node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QJsonValue keyVal = item["key"];
        if (!keyVal.isDouble() || (keyVal.toInt() != keyVal.toDouble())) {
            success = false;
        }
        int key = keyVal.toInt();
        Block value = Block_fromJson(item["value"], &callSuccess);
        if (!callSuccess) {
            success = false;
        }
        obj.insert(key, value);
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}
