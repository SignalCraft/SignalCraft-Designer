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
    BlockType sourceBlockType = source->blockType;
    BlockPin sourcePin = std::make_pair(sourceBlockID, sourcePinName);
    Block* sink = &blocks[sinkBlockID];
    BlockType sinkBlockType = sink->blockType;
    BlockPin sinkPin = std::make_pair(sinkBlockID, sinkPinName);
    if (sourceBlockType.isPinOutput(QString::fromStdString(sourcePinName))) {
        if (sinkBlockType.isPinOutput(QString::fromStdString(sinkPinName))) {
            // both outputs, error condition
        } else {
            // output to input
            if (sink->inputIsConnected(sinkPinName)) {
                // error condition
            } else {
                source->connectOutput(sourcePinName, sinkPin);
                sink->connectInput(sinkPinName, sourcePin);
            }
        }
    } else {
        if (sinkBlockType.isPinOutput(QString::fromStdString(sinkPinName))) {
            // input to output
            if (source->inputIsConnected(sourcePinName)) {
                // error condition
            } else {
                sink->connectOutput(sinkPinName, sourcePin);
                source->connectInput(sourcePinName, sinkPin);
            }
        } else {
            // both inputs, must search
        }
    }
}

void FlowChart::moveBlock(int blockIndex, double xPos, double yPos) {
    blocks[blockIndex].xPos = xPos;
    blocks[blockIndex].yPos = yPos;
}

std::pair<double, double> FlowChart::blockPos(int blockIndex) {
    return std::make_pair(blocks[blockIndex].xPos, blocks[blockIndex].yPos);
}
