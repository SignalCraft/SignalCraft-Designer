#include "flowchart/block.h"

#include <QString>
#include <QPointF>
#include "flowchart/blocktype.h"
#include "flowchart/blockpin.h"

Block::Block() {
    m_blockType = BlockType();
}

Block::Block(BlockType blockType, QPointF pos) {
    m_blockType = blockType;
    m_pos = pos;
    m_optionValues = blockType.defaultOptionValues();
}

Block::Block(BlockType blockType, QPointF pos, QHash<QString, BlockPin> inputConnections, QHash< QString, QSet< BlockPin > > outputConnections) : Block(blockType, pos) {
    m_inputConnections = inputConnections;
    m_outputConnections = outputConnections;
}

bool Block::isValid() const {
    return m_blockType.isValid();
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

BlockType Block::blockType() const {
    return m_blockType;
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
