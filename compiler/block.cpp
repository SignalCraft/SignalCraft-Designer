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
    m_inputConnections[inputPinName] = outputPin;
}

void Block::disconnectInput(QString inputPinName) {
    m_inputConnections.remove(inputPinName);
}

void Block::setPos(QPointF pos) {
    m_pos = pos;
}

void Block::setOptionValues(QHash<QString, QString> optionValues) {
    m_optionValues = optionValues;
}

bool Block::inputIsConnected(QString inputPinName) const {
    return (bool)m_inputConnections.count(inputPinName);
}

QPointF Block::pos() const {
    return m_pos;
}

QString Block::blockTypeName() const {
    return m_blockTypeName;
}

QHash<QString, BlockPin> Block::inputConnections() const {
    return m_inputConnections;
}

QHash< QString, QSet< BlockPin > > Block::outputConnections() const {
    return m_outputConnections;
}

QHash<QString, QString> Block::optionValues() const {
    return m_optionValues;
}

QJsonValue Block_toJson(Block obj) {
    QJsonObject nodeObj;
    nodeObj["blockTypeName"] = obj.blockTypeName();
    nodeObj["pos"] = QPointF_toJson(obj.pos());
    nodeObj["inputConnections"] = QHash_QString_BlockPin_toJson(obj.inputConnections());
    nodeObj["outputConnections"] = QHash_QString_QSet_BlockPin_toJson(obj.outputConnections());
    return nodeObj;
}

Block Block_fromJson(QJsonValue node) {
    QJsonObject nodeObj = node.toObject();
    QString blockTypeName = nodeObj["blockTypeName"].toString();
    QPointF pos = QPointF_fromJson(nodeObj["pos"]);
    QHash<QString, BlockPin> inputConnections = QHash_QString_BlockPin_fromJson(nodeObj["inputConnections"]);
    QHash<QString, QSet<BlockPin>> outputConnections = QHash_QString_QSet_BlockPin_fromJson(nodeObj["outputConnections"]);
    return Block(blockTypeName, pos, inputConnections, outputConnections);
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

QHash<int, Block> QHash_int_Block_fromJson(QJsonValue node) {
    QHash<int, Block> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        int key = item["key"].toInt();
        Block value = Block_fromJson(item["value"]);
        obj.insert(key, value);
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

QMap<int, Block> QMap_int_Block_fromJson(QJsonValue node) {
    QMap<int, Block> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        int key = item["key"].toInt();
        Block value = Block_fromJson(item["value"]);
        obj.insert(key, value);
    }
    return obj;
}
