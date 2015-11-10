#include "compiler.h"

#include <string>
#include <fstream>
#include <iostream>
#include <deque>
#include <tuple>
#include <functional>
#include <algorithm>

using namespace std;

/* Implementation note: wire naming convention
 *
 * All wire names must be unique. To ensure uniqueness, their names are a
 * combination of the block number and pin name of the pin that drives it,
 * as follows:
 *
 * wire_<blocknumber>_<pinname>
 */

string generatePicCode(FlowChart flow) {
    unordered_set<string> blockNames = extractUniqueBlockNames(flow);
    string mainFile = "int main() {\n\n";
    unordered_set<int> expanded;
    deque<int> toBeExpanded = extractInputBlocks(flow);
    unordered_set<string> wires = extractWireNames(flow);
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
                for(auto output : block.outputConnections) {
                    for(auto element : output.second){
                      int outIndex = element.first;
                      if (expanded.count(outIndex) <= 0) {
                        toBeExpanded.push_front(outIndex);
                      }
                    }
                }
                // write this node's function call
                vector<BlockPin> wireBlockPins;
                for (QString inputPinNameQ : block.blockType.inputs.keys()) {
                    string inputPinName = inputPinNameQ.toStdString();
                    if (!block.inputIsConnected(inputPinName)) {
                        // error: bad structure
                        return "";
                    } else {
                        BlockPin wireSource = block.inputConnections[inputPinName];
                        wireBlockPins.push_back(wireSource);
                    }
                }
                for (QString outputPinNameQ : block.blockType.outputs.keys()) {
                    string outputPinName = outputPinNameQ.toStdString();
                    BlockPin outputBlockPin(blockIndex, outputPinName);
                    wireBlockPins.push_back(outputBlockPin);
                }
                string funcCall = block.blockType.name.toStdString();
                funcCall += "(";
                for (int i = 0; i < wireBlockPins.size(); i++) {
                    BlockPin wireSource = wireBlockPins[i];
                    funcCall += "&wire_";
                    funcCall += to_string(wireSource.first);
                    funcCall += "_";
                    funcCall += wireSource.second;
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

    string includesFile = "";
    for (string blockName : blockNames) {
        includesFile += "#include \"";
        includesFile += blockName;
        includesFile += "\"\n";
    }
    includesFile += "\n";

    string declarationsFile = "";
    for (string wireName : wires) {
        declarationsFile += "int ";
        declarationsFile += wireName;
        declarationsFile += ";\n";
    }
    declarationsFile += "\n";

    return includesFile + declarationsFile + mainFile;
}

unordered_set<string> extractUniqueBlockNames(FlowChart flow) {
    unordered_set<string> blockNames;
    for(auto element : flow.blocks) {
        Block block =  element.second;
        // make sure this block's name is in the blockNames set
        blockNames.insert(block.blockType.name.toStdString());
    }
    return blockNames;
}

deque<int> extractInputBlocks(FlowChart flow) {
    deque<int> inputBlocks;
    for(auto element : flow.blocks) {
        int i = element.first;
        Block block =  element.second;
        // If this is an input block, make sure it's expanded first
        if(block.inputConnections.empty()) {
            inputBlocks.push_back(i);
        }
    }
    return inputBlocks;
}

unordered_set<string> extractWireNames(FlowChart flow) {
    unordered_set<string> wireNames;
    for(auto element : flow.blocks) {
        int i = element.first;
        Block block =  element.second;
        // for each output connection
        for (auto element : block.outputConnections) {
            // construct wire name
            string pinName = element.first;
            string wireName = "wire_";
            wireName += to_string(i);
            wireName += "_";
            wireName += pinName;
            wireNames.insert(wireName);
        }
    }
    return wireNames;
}

bool isExpandable(Block block, std::unordered_set<int> expanded) {
    bool found_all = true;
    for(auto input : block.inputConnections) {
        int blockNum = input.second.first;
        if(expanded.find(blockNum) == expanded.end()) {
            found_all = false;
            break;
        }
    }
    return found_all;
}
