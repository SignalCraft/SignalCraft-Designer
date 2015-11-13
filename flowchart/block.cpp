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

Block::Block(BlockType _blockType, QPointF _pos) {
    blockType = _blockType;
    pos = _pos;
}

void Block::connectOutput(QString outputPinName, BlockPin inputPin) {
    outputConnections[outputPinName].insert(inputPin);
}

void Block::connectInput(QString inputPinName, BlockPin outputPin) {
    inputConnections[inputPinName] = outputPin;
}

bool Block::inputIsConnected(QString inputPinName) {
    return (bool)inputConnections.count(inputPinName);
}
