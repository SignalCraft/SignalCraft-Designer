#include "flowchart/flowchart.h"

#include <QPointF>
#include <QString>
#include "flowchart/block.h"
#include "flowchart/blocktype.h"
#include "flowchart/blockpin.h"

FlowChart::FlowChart() {}

FlowChart::FlowChart(QHash<int, Block> blocks) {
    m_blocks = blocks;
}

int FlowChart::addBlock(BlockType blockType, QPointF pos) {
    Block b(blockType, pos);
    m_blocks[m_currentIndex] = b;
    return m_currentIndex++;
}

void FlowChart::connect(int sourceBlockID, QString sourcePinName, int sinkBlockID, QString sinkPinName) {
    Block* source = &m_blocks[sourceBlockID];
    BlockType sourceBlockType = source->blockType();
    BlockPin sourcePin(sourceBlockID, sourcePinName);
    Block* sink = &m_blocks[sinkBlockID];
    BlockType sinkBlockType = sink->blockType();
    BlockPin sinkPin(sinkBlockID, sinkPinName);
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
    m_blocks[blockIndex].setPos(pos);
}

void FlowChart::setBlockOptionValues(int blockIndex, QHash<QString, QString> optionValues) {
    m_blocks[blockIndex].setOptionValues(optionValues);
}

QPointF FlowChart::blockPos(int blockIndex) const {
    return block(blockIndex).pos();
}

QHash<int, Block> FlowChart::blocks() const {
    return m_blocks;
}

Block FlowChart::block(int blockIndex) const {
    return blocks()[blockIndex];
}
