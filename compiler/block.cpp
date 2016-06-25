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
    Q_ASSERT(isValid());
    Q_ASSERT(!outputPinName.isEmpty());
    Q_ASSERT(inputPin.isValid());
    m_outputConnections[outputPinName].insert(inputPin);
}

void Block::disconnectOutput(QString outputPinName, BlockPin inputPin) {
    Q_ASSERT(isValid());
    Q_ASSERT(inputPin.isValid());
    Q_ASSERT(m_outputConnections.contains(outputPinName));
    Q_ASSERT(m_outputConnections.value(outputPinName).contains(inputPin));
    m_outputConnections[outputPinName].remove(inputPin);
}

void Block::connectInput(QString inputPinName, BlockPin outputPin) {
    Q_ASSERT(isValid());
    Q_ASSERT(!inputPinName.isEmpty());
    Q_ASSERT(outputPin.isValid());
    m_inputConnections.insert(inputPinName,outputPin);
}

void Block::disconnectInput(QString inputPinName) {
    Q_ASSERT(isValid());
    Q_ASSERT(m_inputConnections.contains(inputPinName));
    m_inputConnections.remove(inputPinName);
}

void Block::setPos(QPointF pos) {
    Q_ASSERT(isValid());
    m_pos = pos;
}

void Block::setOptionValue(QString optionName, QString value) {
    Q_ASSERT(isValid());
    Q_ASSERT(!optionName.isEmpty());
    Q_ASSERT(!value.isEmpty());
    m_optionValues.insert(optionName, value);
}

void Block::resetOptionValues() {
    Q_ASSERT(isValid());
    m_optionValues = QHash<QString, QString>();
}

QPointF Block::pos() const {
    Q_ASSERT(isValid());
    return m_pos;
}

QString Block::blockTypeName() const {
    Q_ASSERT(isValid());
    return m_blockTypeName;
}

bool Block::hasInputConnections() const {
    Q_ASSERT(isValid());
    return !m_inputConnections.isEmpty();
}

BlockPin Block::inputConnection(QString inputPinName) const {
    Q_ASSERT(isValid());
    return m_inputConnections.value(inputPinName);
}

QSet<BlockPin> Block::outputConnection(QString outputPinName) const {
    Q_ASSERT(isValid());
    return m_outputConnections.value(outputPinName);
}

QString Block::optionValue(QString optionName) const {
    Q_ASSERT(isValid());
    return m_optionValues.value(optionName);
}

QString Block::optionValue(QString optionName, QString defaultValue) const {
    Q_ASSERT(isValid());
    return m_optionValues.value(optionName, defaultValue);
}

QJsonValue Block::toJson() const {
    Q_ASSERT(isValid());
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
