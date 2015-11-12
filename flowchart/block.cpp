#include "flowchart/block.h"

#include <QString>
#include <QPointF>
#include "flowchart/blocktype.h"

uint qHash(const BlockPin b) {
    return (b.first * 31) + qHash(b.second);
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
