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

FlowChart::FlowChart(QHash<int, Block> blocks, QHash<QString, BlockType> *blockTypes) {
    m_blocks = blocks;
    for (int blockIndex : blocks.keys()) {
        if (blockIndex >= m_currentIndex) {
            m_currentIndex = blockIndex + 1;
        }
    }
    m_blockTypes = blockTypes;
}

int FlowChart::addBlock(QString blockTypeName, QPointF pos) {
    Block b(blockTypeName, pos);
    m_blocks[m_currentIndex] = b;
    return m_currentIndex++;
}

void FlowChart::removeBlock(int blockIndex) {
    Block b = m_blocks[blockIndex];
    BlockType bt = m_blockTypes->value(b.blockTypeName());
    for (QString inputPinName : bt.inputs().keys()) {
        BlockPin preBlockPin = b.inputConnection(inputPinName);
        m_blocks[preBlockPin.blockNum()].disconnectOutput(preBlockPin.pinName(), BlockPin(blockIndex, inputPinName));
    }
    for (QString outputPinName : bt.outputs().keys()) {
        QSet<BlockPin> postBlockPins = b.outputConnection(outputPinName);
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
            if (sink->inputConnection(second.pinName()).isValid()) {
                // error condition
            } else {
                source->connectOutput(first.pinName(), second);
                sink->connectInput(second.pinName(), first);
            }
        }
    } else {
        if (sinkBlockType.isPinOutput(second.pinName())) {
            // input to output
            if (source->inputConnection(first.pinName()).isValid()) {
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
    for (QString optionName : optionValues.keys()) {
        QString optionValue = optionValues.value(optionName);
        m_blocks[blockIndex].setOptionValue(optionName, optionValue);
    }
}

QList<int> FlowChart::blockIndeces() const {
    return m_blocks.keys();
}

QPointF FlowChart::blockPos(int blockIndex) const {
    return m_blocks.value(blockIndex).pos();
}

const QHash<QString, BlockType> *FlowChart::blockTypes() const {
    return m_blockTypes;
}

QString FlowChart::blockTypeName(int blockIndex) const {
    return m_blocks.value(blockIndex).blockTypeName();
}

BlockType FlowChart::blockType(int blockIndex) const {
    return m_blockTypes->value(blockTypeName(blockIndex));
}

BlockPin FlowChart::blockInputConnection(int blockIndex, QString inputPinName) const {
    return m_blocks.value(blockIndex).inputConnection(inputPinName);
}

BlockPin FlowChart::blockInputConnection(BlockPin input) const {
    return blockInputConnection(input.blockNum(), input.pinName());
}

QSet<BlockPin> FlowChart::blockOutputConnection(int blockIndex, QString outputPinName) const {
    return m_blocks.value(blockIndex).outputConnection(outputPinName);
}

QSet<BlockPin> FlowChart::blockOutputConnection(BlockPin output) const {
    return blockOutputConnection(output.blockNum(), output.pinName());
}

QString FlowChart::blockOptionValue(int blockIndex, QString optionName, QString defaultValue) const {
    return m_blocks.value(blockIndex).optionValue(optionName, defaultValue);
}

bool FlowChart::blockHasInputConnections(int blockIndex) const {
    return m_blocks.value(blockIndex).hasInputConnections();
}

QJsonValue FlowChart::toJson() const {
    QJsonObject nodeObj;
    nodeObj["blocks"] = QHash_int_Block_toJson(m_blocks);
    return nodeObj;
}

QJsonValue FlowChart_toJson(FlowChart obj) {
    return obj.toJson();
}

FlowChart FlowChart_fromJsonWithBlockTypes(QJsonValue node, QHash<QString, BlockType> *blockTypes, bool *ok) {
    bool success = true;
    bool callSuccess;
    QJsonObject nodeObj = node.toObject();
    QHash<int, Block> blocks = QHash_int_Block_fromJson(nodeObj["blocks"], &callSuccess);
    if (!callSuccess) {
        success = false;
    }
    if (ok) {
        *ok = success;
    }
    return FlowChart(blocks, blockTypes);
}
