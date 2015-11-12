#include "flowchart/flowchart.h"

#include <QPointF>
#include <QString>
#include "flowchart/block.h"
#include "flowchart/blocktype.h"

FlowChart::FlowChart() {}

int FlowChart::addBlock(BlockType blockType, QPointF pos) {
    Block b(blockType, pos);
    blocks[currentIndex] = b;
    return currentIndex++;
}

void FlowChart::connect(int sourceBlockID, QString sourcePinName, int sinkBlockID, QString sinkPinName) {
    Block* source = &blocks[sourceBlockID];
    BlockType sourceBlockType = source->blockType;
    BlockPin sourcePin = std::make_pair(sourceBlockID, sourcePinName);
    Block* sink = &blocks[sinkBlockID];
    BlockType sinkBlockType = sink->blockType;
    BlockPin sinkPin = std::make_pair(sinkBlockID, sinkPinName);
    if (sourceBlockType.isPinOutput(sourcePinName)) {
        if (sinkBlockType.isPinOutput(sinkPinName)) {
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
        if (sinkBlockType.isPinOutput(sinkPinName)) {
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

void FlowChart::moveBlock(int blockIndex, QPointF pos) {
    blocks[blockIndex].pos = pos;
}

QPointF FlowChart::blockPos(int blockIndex) {
    return blocks[blockIndex].pos;
}
