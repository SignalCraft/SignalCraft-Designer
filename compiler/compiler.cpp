#include "compiler.h"

#include <QString>
#include <QList>
#include <QSet>
#include <QVector>
#include <QHash>
#include "flowchart/blockpin.h"
#include "flowchart/block.h"
#include "flowchart/blocktype.h"

using namespace std;

/* Implementation note: wire naming convention
 *
 * All wire names must be unique. To ensure uniqueness, their names are a
 * combination of the block number and pin name of the pin that drives it,
 * as follows:
 *
 * wire_<blocknumber>_<pinname>
 */

QString generatePicCode(const FlowChart flow) {
    const QHash<QString, BlockType> *blockTypes = flow.blockTypes();
    QSet<QString> blockNames = extractUniqueBlockNames(flow);
    QString mainFile = "int main() {\n\nSystemInit();\ninit_adc();\ninit_dac();\nWDT->WDT_MR |= WDT_MR_WDDIS;\n\nwhile (1) {\n\n";
    QSet<int> expanded;
    QList<int> toBeExpanded = extractInputBlocks(flow);
    QSet<QString> wires = extractWireNames(flow);
    QList<QString> structInstances;
    // directed graph traversal: write the sequence of functions
    while(!toBeExpanded.empty()) {
        int blockIndex = toBeExpanded.front();
        toBeExpanded.pop_front();
        // if this block has not been expanded yet
        if (expanded.find(blockIndex) == expanded.end()) {
            Block block = flow.block(blockIndex);
            BlockType blockType = blockTypes->value(block.blockTypeName());
            // check if all this block's inputs have been expanded
            bool found_all = isExpandable(block, expanded);
            if(found_all) {
                // mark this node as expanded
                expanded.insert(blockIndex);
                // add all of this node's outputs to the front of the queue
                for(auto output : block.outputConnections().values()) {
                    for(BlockPin element : output){
                      int outIndex = element.blockNum();
                      if (!expanded.contains(outIndex)) {
                        toBeExpanded.push_front(outIndex);
                      }
                    }
                }
                // write this node's function call
                QVector<BlockPin> wireBlockPins;
                for (QString inputPinName : blockType.inputs().keys()) {
                    if (!block.inputIsConnected(inputPinName)) {
                        // error: bad structure
                        return "";
                    } else {
                        BlockPin wireSource = block.inputConnections()[inputPinName];
                        wireBlockPins.push_back(wireSource);
                    }
                }
                for (QString outputPinName : blockType.outputs().keys()) {
                    BlockPin outputBlockPin(blockIndex, outputPinName);
                    wireBlockPins.push_back(outputBlockPin);
                }
                QString funcCall = block.blockTypeName();
                funcCall += "(";
                funcCall += "&block_options_";
                funcCall += QString::number(blockIndex);
                if (0 < wireBlockPins.size()) {
                    funcCall += ",";
                }
                for (int i = 0; i < wireBlockPins.size(); i++) {
                    BlockPin wireSource = wireBlockPins[i];
                    funcCall += "&wire_";
                    funcCall += QString::number(wireSource.blockNum());
                    funcCall += "_";
                    funcCall += wireSource.pinName();
                    if (i < wireBlockPins.size() - 1) {
                        funcCall += ",";
                    }
                }
                funcCall += ");";
                mainFile += funcCall;
                mainFile += "\n";
                // write this node's struct instance
                QString structInstance = "struct ";
                structInstance += block.blockTypeName();
                structInstance += "_options ";
                structInstance += "block_options_";
                structInstance += QString::number(blockIndex);
                structInstance += ";\n";
                QHash<QString, QString> optionValues = blockType.resultingOptionValues(block.optionValues());
                for (QString optionName : blockType.options().keys()) {
                    QString optionValue = optionValues[optionName];
                    structInstance += "block_options_";
                    structInstance += QString::number(blockIndex);
                    structInstance += ".";
                    structInstance += optionName;
                    structInstance += " = ";
                    structInstance += optionValue; // TODO: factor in data type
                    structInstance += ";\n";
                }
                structInstances.append(structInstance);
            } else {
               toBeExpanded.push_back(blockIndex);
            }
        }
    }
    mainFile += "\n}\n\nreturn 0;\n\n}";

    QString includesFile = "#include \"sam.h\"\n#include \"adc.h\"\n#include \"dac.h\"\n";
    for (QString blockName : blockNames) {
        includesFile += "#include \"blocks/";
        includesFile += blockName;
        includesFile += ".h\"\n";
    }
    includesFile += "\n";

    QString structInstancesFile;
    for (QString structInstance : structInstances) {
        structInstancesFile += structInstance;
    }
    structInstancesFile += "\n";

    QString declarationsFile = "";
    for (QString wireName : wires) {
        declarationsFile += "int ";
        declarationsFile += wireName;
        declarationsFile += ";\n";
    }
    declarationsFile += "\n";

    return includesFile + structInstancesFile + declarationsFile + mainFile;
}

QSet<QString> extractUniqueBlockNames(FlowChart flow) {
    QSet<QString> blockNames;
    for(Block block : flow.blocks().values()) {
        // make sure this block's name is in the blockNames set
        blockNames.insert(block.blockTypeName());
    }
    return blockNames;
}

QList<int> extractInputBlocks(FlowChart flow) {
    QList<int> inputBlocks;
    for(int blockIndex : flow.blocks().keys()) {
        Block block = flow.block(blockIndex);
        // If this is an input block, make sure it's expanded first
        if(block.inputConnections().empty()) {
            inputBlocks.push_back(blockIndex);
        }
    }
    return inputBlocks;
}

QSet<QString> extractWireNames(FlowChart flow) {
    QSet<QString> wireNames;
    for(int blockIndex : flow.blocks().keys()) {
        Block block = flow.block(blockIndex);
        // for each output connection
        for (QString pinName : block.outputConnections().keys()) {
            // construct wire name
            QString wireName = "wire_";
            wireName += QString::number(blockIndex);
            wireName += "_";
            wireName += pinName;
            wireNames.insert(wireName);
        }
    }
    return wireNames;
}

bool isExpandable(Block block, QSet<int> expanded) {
    bool found_all = true;
    for(BlockPin bp : block.inputConnections().values()) {
        int blockNum = bp.blockNum();
        if(expanded.find(blockNum) == expanded.end()) {
            found_all = false;
            break;
        }
    }
    return found_all;
}
