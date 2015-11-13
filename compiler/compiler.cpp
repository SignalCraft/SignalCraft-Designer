#include "compiler.h"

#include <QString>
#include <QList>
#include <QSet>
#include <QVector>

using namespace std;

/* Implementation note: wire naming convention
 *
 * All wire names must be unique. To ensure uniqueness, their names are a
 * combination of the block number and pin name of the pin that drives it,
 * as follows:
 *
 * wire_<blocknumber>_<pinname>
 */

QString generatePicCode(FlowChart flow) {
    QSet<QString> blockNames = extractUniqueBlockNames(flow);
    QString mainFile = "int main() {\n\n";
    QSet<int> expanded;
    QList<int> toBeExpanded = extractInputBlocks(flow);
    QSet<QString> wires = extractWireNames(flow);
    // directed graph traversal: write the sequence of functions
    while(!toBeExpanded.empty()) {
        int blockIndex = toBeExpanded.front();
        toBeExpanded.pop_front();
        // if this block has not been expanded yet
        if (expanded.find(blockIndex) == expanded.end()) {
            Block block = flow.blocks[blockIndex];
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
                for (QString inputPinName : block.blockType().inputs.keys()) {
                    if (!block.inputIsConnected(inputPinName)) {
                        // error: bad structure
                        return "";
                    } else {
                        BlockPin wireSource = block.inputConnections()[inputPinName];
                        wireBlockPins.push_back(wireSource);
                    }
                }
                for (QString outputPinName : block.blockType().outputs.keys()) {
                    BlockPin outputBlockPin(blockIndex, outputPinName);
                    wireBlockPins.push_back(outputBlockPin);
                }
                QString funcCall = block.blockType().name;
                funcCall += "(";
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
            } else {
               toBeExpanded.push_back(blockIndex);
            }
        }
    }
    mainFile += "\n}";

    QString includesFile = "";
    for (QString blockName : blockNames) {
        includesFile += "#include \"";
        includesFile += blockName;
        includesFile += "\"\n";
    }
    includesFile += "\n";

    QString declarationsFile = "";
    for (QString wireName : wires) {
        declarationsFile += "int ";
        declarationsFile += wireName;
        declarationsFile += ";\n";
    }
    declarationsFile += "\n";

    return includesFile + declarationsFile + mainFile;
}

QSet<QString> extractUniqueBlockNames(FlowChart flow) {
    QSet<QString> blockNames;
    for(Block block : flow.blocks.values()) {
        // make sure this block's name is in the blockNames set
        blockNames.insert(block.blockType().name);
    }
    return blockNames;
}

QList<int> extractInputBlocks(FlowChart flow) {
    QList<int> inputBlocks;
    for(int i : flow.blocks.keys()) {
        Block block =  flow.blocks[i];
        // If this is an input block, make sure it's expanded first
        if(block.inputConnections().empty()) {
            inputBlocks.push_back(i);
        }
    }
    return inputBlocks;
}

QSet<QString> extractWireNames(FlowChart flow) {
    QSet<QString> wireNames;
    for(int i : flow.blocks.keys()) {
        Block block =  flow.blocks[i];
        // for each output connection
        for (QString pinName : block.outputConnections().keys()) {
            // construct wire name
            QString wireName = "wire_";
            wireName += QString::number(i);
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
