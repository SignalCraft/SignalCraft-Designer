#include "compiler/compiler.h"

#include <QString>
#include <QList>
#include <QSet>
#include <QVector>
#include <QHash>
#include "flowchart/blockpin.h"
#include "flowchart/block.h"
#include "flowchart/blocktype.h"
#include "compiler/compiledblockinfo.h"

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
    QString mainFilePrefix = "int main() {\n\nSystemInit();\ninit_adc();\ninit_dac();\nWDT->WDT_MR |= WDT_MR_WDDIS;\n\n";
    QString mainFile = "while (1) {\n\ntrigger_adc();\n\n";
    QSet<int> expanded;
    QList<int> toBeExpanded = extractInputBlocks(flow);
    QHash<int, CompiledBlockInfo> compiledBlocks;
    QString declarationsFile;
    QList<QString> structInitializers;
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
                CompiledBlockInfo compiledBlock = CompiledBlockInfo::compileBlock(blockIndex, block, compiledBlocks, blockTypes);
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
