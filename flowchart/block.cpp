#include "flowchart/block.h"

#include <QString>
#include <QPointF>
#include "flowchart/blocktype.h"

BlockPin::BlockPin() {
    m_blockNum = -1;
    m_pinName = "";
}

BlockPin::BlockPin(int blockNum, QString pinName) {
    m_blockNum = blockNum;
    m_pinName = pinName;
}

bool BlockPin::operator==(const BlockPin &other) const {
    return (blockNum() == other.blockNum()) && (pinName() == other.pinName());
}

int BlockPin::blockNum() const {
    return m_blockNum;
}

QString BlockPin::pinName() const {
    return m_pinName;
}

uint qHash(const BlockPin b) {
    return (b.blockNum() * 31) + qHash(b.pinName());
}

Block::Block() {}

Block::Block(BlockType blockType, QPointF pos) {
    m_blockType = blockType;
    m_pos = pos;
}

Block::Block(BlockType blockType, QPointF pos, QHash<QString, BlockPin> inputConnections, QHash< QString, QSet< BlockPin > > outputConnections) {
    m_blockType = blockType;
    m_pos = pos;
    m_inputConnections = inputConnections;
    m_outputConnections = outputConnections;
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

bool Block::inputIsConnected(QString inputPinName) const {
    return (bool)m_inputConnections.count(inputPinName);
}

QPointF Block::pos() const {
    return m_pos;
}

BlockType Block::blockType() const {
    return m_blockType;
}

QHash<QString, BlockPin> Block::inputConnections() const {
    return m_inputConnections;
}

QHash< QString, QSet< BlockPin > > Block::outputConnections() const {
    return m_outputConnections;
}
