#include "flowchart/block.h"

#include "json/json.h"

Block::Block() {}

Block::Block(BlockType _blockType, double _xPos, double _yPos) {
    blockType = _blockType;
    xPos = _xPos;
    yPos = _yPos;
}

void Block::connectOutput(std::string outputPinName, BlockPin inputPin) {
    outputConnections[outputPinName].insert(inputPin);
}

void Block::connectInput(std::string inputPinName, BlockPin outputPin) {
    inputConnections[inputPinName] = outputPin;
}
