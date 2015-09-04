#include "flowchart/flowchart.h"

#include "flowchart/block.h"
#include "flowchart/blocktype.h"
#include <utility>
#include "json/json.h"

FlowChart::FlowChart() {}

int FlowChart::addBlock(BlockType blockType, double xPos, double yPos) {
    Block b(blockType, xPos, yPos);
    blocks[currentIndex] = b;
    return currentIndex++;
}

void FlowChart::connect(int sourceBlockID, std::string sourcePinName, int sinkBlockID, std::string sinkPinName) {
    Block* source = &blocks[sourceBlockID];
    BlockPin sourcePin = std::make_pair(sourceBlockID, sourcePinName);
    Block* sink = &blocks[sinkBlockID];
    BlockPin sinkPin = std::make_pair(sinkBlockID, sinkPinName);
    // connect source block to sink pin
    source->connectOutput(sourcePinName, sinkPin);
    // connect sink block to source pin
    sink->connectInput(sinkPinName, sourcePin);
}

void FlowChart::moveBlock(int blockIndex, double xPos, double yPos) {
    blocks[blockIndex].xPos = xPos;
    blocks[blockIndex].yPos = yPos;
}

std::pair<double, double> FlowChart::blockPos(int blockIndex) {
    return std::make_pair(blocks[blockIndex].xPos, blocks[blockIndex].yPos);
}
