#include "flowchart/flowchart.h"

#include "flowchart/block.h"
#include <utility>
#include "json/json.h"

FlowChart::FlowChart() {}

int FlowChart::addBlock(std::string blockTypeName, double xPos, double yPos) {
    Block b(blockTypeName, xPos, yPos);
    blocks[currentIndex] = b;
    return currentIndex++;
}

void FlowChart::connect(int sourceBlockID, std::string sourcePinName, int sinkBlockID, std::string sinkPinName) {
    Block* source = &blocks[sourceBlockID];
    BlockPin sourcePin = std::make_pair(sourceBlockID, sourcePinName);
    Block* sink = &blocks[sinkBlockID];
    BlockPin sinkPin = std::make_pair(sinkBlockID, sinkPinName);
    // connect source block to sink pin
    source->connectOutput(sourcePinName, sinkPin);
    // connect sink block to source pin
    sink->connectInput(sinkPinName, sourcePin);
}

FlowChart FlowChart::jsonParseFlowChart(Json::Value node) {
    FlowChart f;
    f.blocks = jsonParseBlocks(node["blocks"]);
    return f;
}

Json::Value FlowChart::jsonComposeFlowChart(FlowChart f) {
    Json::Value node;
    node["blocks"] = jsonComposeBlocks(f.blocks);
    return node;
}

std::unordered_map<int, Block> FlowChart::jsonParseBlocks(Json::Value node) {
    std::unordered_map<int, Block> map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[itr.key().asInt()] = Block::jsonParseBlock(*itr);
    }
    return map;
}

Json::Value FlowChart::jsonComposeBlocks(std::unordered_map<int, Block> map) {
    Json::Value node;
    for (auto kvpair : map) {
        node[kvpair.first] = Block::jsonComposeBlock(kvpair.second);
    }
    return node;
}

