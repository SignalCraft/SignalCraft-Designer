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

void FlowChart::connect(BlockPin first, BlockPin second) {
    Block* source = &m_blocks[first.blockNum()];
    BlockType sourceBlockType = source->blockType();
    Block* sink = &m_blocks[second.blockNum()];
    BlockType sinkBlockType = sink->blockType();
    if (sourceBlockType.isPinOutput(first.pinName())) {
        if (sinkBlockType.isPinOutput(second.pinName())) {
            // both outputs, error condition
        } else {
            // output to input
            if (sink->inputIsConnected(second.pinName())) {
                // error condition
            } else {
                source->connectOutput(first.pinName(), second);
                sink->connectInput(second.pinName(), first);
            }
        }
    } else {
        if (sinkBlockType.isPinOutput(second.pinName())) {
            // input to output
            if (source->inputIsConnected(first.pinName())) {
                // error condition
            } else {
                sink->connectOutput(second.pinName(), first);
                source->connectInput(first.pinName(), second);
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
