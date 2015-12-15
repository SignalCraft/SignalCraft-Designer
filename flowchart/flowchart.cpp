#include "flowchart/flowchart.h"

#include <QPointF>
#include <QString>
#include "flowchart/block.h"
#include "flowchart/blocktype.h"
#include "flowchart/blockpin.h"
#include <QJsonValue>
#include <QJsonObject>
#include "jsonforqt.h"
#include <QMap>

FlowChart::FlowChart() { }

FlowChart::FlowChart(QHash<int, Block> blocks) {
    m_blocks = blocks;
}

int FlowChart::addBlock(QString blockTypeName, QPointF pos) {
    Block b(blockTypeName, pos);
    m_blocks[m_currentIndex] = b;
    return m_currentIndex++;
}

void FlowChart::setBlockTypes(QHash<QString, BlockType> *blockTypes) {
    m_blockTypes = blockTypes;
}

void FlowChart::connect(BlockPin first, BlockPin second) {
    Block* source = &m_blocks[first.blockNum()];
    BlockType sourceBlockType = m_blockTypes->value(source->blockTypeName());
    Block* sink = &m_blocks[second.blockNum()];
    BlockType sinkBlockType = m_blockTypes->value(sink->blockTypeName());
    if (sourceBlockType.isPinOutput(first.pinName())) {
        if (sinkBlockType.isPinOutput(second.pinName())) {
            // both outputs, error condition
        } else {
            // output to input
            if (sink->inputIsConnected(second.pinName())) {
                // error condition
            } else {
                connectOutputToInput(first, second);
            }
        }
    } else {
        if (sinkBlockType.isPinOutput(second.pinName())) {
            // input to output
            if (source->inputIsConnected(first.pinName())) {
                // error condition
            } else {
                connectOutputToInput(second, first);
            }
        } else {
            // both inputs, must search
        }
    }
}

void FlowChart::connectOutputToInput(BlockPin output, BlockPin input) {
    Block* outputBlock = &m_blocks[output.blockNum()];
    Block* inputBlock = &m_blocks[input.blockNum()];
    outputBlock->connectOutput(output.pinName(), input);
    inputBlock->connectInput(input.pinName(), output);
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

const QHash<QString, BlockType> *FlowChart::blockTypes() const {
    return m_blockTypes;
}

Block FlowChart::block(int blockIndex) const {
    return blocks()[blockIndex];
}

QJsonValue FlowChart_toJson(FlowChart obj) {
    QJsonObject nodeObj;
    nodeObj["blocks"] = QHash_int_Block_toJson(obj.blocks());
    return nodeObj;
}

FlowChart FlowChart_fromJson(QJsonValue node) {
    QJsonObject nodeObj = node.toObject();
    QHash<int, Block> blocks = QHash_int_Block_fromJson(nodeObj["blocks"]);
    return FlowChart(blocks);
}
