#ifndef FLOWCHART_H
#define FLOWCHART_H

#include <vector>
#include <utility>
#include <String>
#include <unordered_map>
#include "flowchart/block.h"
#include "flowchart/blocktype.h"
#include "json/json.h"

class FlowChart
{
public:
    static std::unordered_map<std::string, BlockType> BLOCK_TYPES;
public:
    FlowChart();
    int addBlock(std::string blockType, double xPos, double yPos);
    void connect(int sourceBlockID, std::string sourcePinName, int sinkBlockID, std::string sinkPinName);
    std::unordered_map<int, Block> blocks;
    static FlowChart jsonParseFlowChart(Json::Value node);
    static Json::Value jsonComposeFlowChart(FlowChart b);
    static std::unordered_map<int, Block> jsonParseBlocks(Json::Value node);
    static Json::Value jsonComposeBlocks(std::unordered_map<int, Block> map);
protected:
    int currentIndex = 0;
};

#endif // FLOWCHART_H
