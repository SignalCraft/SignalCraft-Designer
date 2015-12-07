#include "flowchart/block.h"

#include <QString>
#include <QPointF>
#include "flowchart/blockpin.h"
#include <QJsonValue>
#include <QJsonObject>
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

void Block::connectInput(QString inputPinName, BlockPin outputPin) {
    m_inputConnections[inputPinName] = outputPin;
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
