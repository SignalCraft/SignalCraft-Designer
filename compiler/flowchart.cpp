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
#include <QList>
#include <QSet>
#include <QVector>
#include <QHash>
#include "compiledblockinfo.h"

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

/* Implementation note: wire naming convention
 *
 * All wire names must be unique. To ensure uniqueness, their names are a
 * combination of the block number and pin name of the pin that drives it,
 * as follows:
 *
 * wire_<blocknumber>_<pinname>
 */

FlowChart::Compiler::Compiler(const FlowChart& flow) : m_flow(flow) { }

QString FlowChart::Compiler::generatePicCode() {
    const QHash<QString, BlockType> *blockTypes = m_flow.blockTypes();
    QSet<QString> blockNames = extractUniqueBlockNames();
    QString mainFilePrefix = "int main() {\n\nSystemInit();\ninit_adc();\ninit_dac();\nWDT->WDT_MR |= WDT_MR_WDDIS;\n\n";
    QString mainFile = "while (1) {\n\ntrigger_adc();\n\n";
    QSet<int> expanded;
    QList<int> toBeExpanded = extractInputBlocks();
    QHash<int, CompiledBlockInfo> compiledBlocks;
    QString declarationsFile;
    QList<QString> structInitializers;
    // directed graph traversal: write the sequence of functions
    while(!toBeExpanded.empty()) {
        int blockIndex = toBeExpanded.front();
        toBeExpanded.pop_front();
        // if this block has not been expanded yet
        if (expanded.find(blockIndex) == expanded.end()) {
            BlockType blockType = m_flow.blockType(blockIndex);
            // check if all this block's inputs have been expanded
            bool found_all = isExpandable(blockIndex, expanded);
            if(found_all) {
                // mark this node as expanded
                expanded.insert(blockIndex);
                // add all of this node's outputs to the front of the queue
                for (QString outputPinName : blockType.outputs().keys()) {
                    QSet<BlockPin> outputBlockPins = m_flow.blockOutputConnection(blockIndex, outputPinName);
                    for(BlockPin element : outputBlockPins){
                      int outIndex = element.blockNum();
                      if (!expanded.contains(outIndex)) {
                        toBeExpanded.push_front(outIndex);
                      }
                    }
                }
                // write this node's function call
                CompiledBlockInfo compiledBlock = CompiledBlockInfo::compileBlock(blockIndex, m_flow.m_blocks[blockIndex], compiledBlocks, blockTypes);
                compiledBlocks[blockIndex] = compiledBlock;
                mainFile += compiledBlock.code();
                // write this node's struct initializer
                QString structInitializer = "";
                QHash<QString, QString> optionValues = compiledBlock.compiledOptionValues();
                for (QString optionName : blockType.options().keys()) {
                    QString optionValue = optionValues[optionName];
                    structInitializer += "int block_options_"; // TODO: factor in data type
                    structInitializer += QString::number(blockIndex);
                    structInitializer += "_";
                    structInitializer += optionName;
                    structInitializer += " = ";
                    structInitializer += optionValue; // TODO: factor in data type
                    structInitializer += ";\n";
                }
                structInitializers.append(structInitializer);
                // write this node's declarations
                declarationsFile += compiledBlock.wireCode();
            } else {
               toBeExpanded.push_back(blockIndex);
            }
        }
    }
    mainFile += "\ntrigger_dac();\n}\n\nreturn 0;\n\n}";

    QString includesFile = "#include \"sam.h\"\n#include \"adc.h\"\n#include \"dac.h\"\n#include <math.h>\n";
    /*
    for (QString blockName : blockNames) {
        includesFile += "#include \"blocks/";
        includesFile += blockName;
        includesFile += ".h\"\n";
    }
    */
    includesFile += "\n";

    QString structInitializersFile;
    for (QString structInitializer : structInitializers) {
        structInitializersFile += structInitializer;
    }
    structInitializersFile += "\n";

    return includesFile + declarationsFile + mainFilePrefix + structInitializersFile + mainFile;
}

QSet<QString> FlowChart::Compiler::extractUniqueBlockNames() {
    QSet<QString> blockNames;
    for(int blockIndex : m_flow.blockIndeces()) {
        // make sure this block's name is in the blockNames set
        blockNames.insert(m_flow.blockTypeName(blockIndex));
    }
    return blockNames;
}

QList<int> FlowChart::Compiler::extractInputBlocks() {
    QList<int> inputBlocks;
    for(int blockIndex : m_flow.blockIndeces()) {
        // If this is an input block, make sure it's expanded first
        if(!m_flow.blockHasInputConnections(blockIndex)) {
            inputBlocks.push_back(blockIndex);
        }
    }
    return inputBlocks;
}

bool FlowChart::Compiler::isExpandable(int blockIndex, QSet<int> expanded) {
    BlockType bt = m_flow.blockType(blockIndex);
    bool found_all = true;
    for(QString inputPinName : bt.inputs().keys()) {
        BlockPin bp = m_flow.blockInputConnection(blockIndex, inputPinName);
        int blockNum = bp.blockNum();
        if(expanded.find(blockNum) == expanded.end()) {
            found_all = false;
            break;
        }
    }
    return found_all;
}

