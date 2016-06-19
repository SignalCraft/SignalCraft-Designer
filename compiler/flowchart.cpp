#include "flowchart.h"

#include <QPointF>
#include <QString>
#include "block.h"
#include "blocktype.h"
#include "blockpin.h"
#include <QJsonValue>
#include <QJsonObject>
#include "jsonforqt.h"
#include <QMap>

FlowChart::FlowChart() { }

FlowChart::FlowChart(QHash<int, Block> blocks) {
    m_blocks = blocks;
    for (int blockIndex : blocks.keys()) {
        if (blockIndex >= m_currentIndex) {
            m_currentIndex = blockIndex + 1;
        }
    }
}

int FlowChart::addBlock(QString blockTypeName, QPointF pos) {
    Block b(blockTypeName, pos);
    m_blocks[m_currentIndex] = b;
    return m_currentIndex++;
}

void FlowChart::setBlockTypes(QHash<QString, BlockType> *blockTypes) {
    m_blockTypes = blockTypes;
}

void FlowChart::removeBlock(int blockIndex) {
    Block b = m_blocks[blockIndex];
    for (QString inputPinName : b.inputConnections().keys()) {
        BlockPin preBlockPin = b.inputConnections().value(inputPinName);
        m_blocks[preBlockPin.blockNum()].disconnectOutput(preBlockPin.pinName(), BlockPin(blockIndex, inputPinName));
    }
    for (QString outputPinName : b.outputConnections().keys()) {
        QSet<BlockPin> postBlockPins = b.outputConnections().value(outputPinName);
        for (BlockPin postBlockPin : postBlockPins) {
            m_blocks[postBlockPin.blockNum()].disconnectInput(postBlockPin.pinName());
        }
    }
    m_blocks.remove(blockIndex);
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
