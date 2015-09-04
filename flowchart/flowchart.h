#ifndef FLOWCHART_H
#define FLOWCHART_H

#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include "flowchart/block.h"
#include "flowchart/blocktype.h"

class FlowChart
{
public:
    FlowChart();
    int addBlock(BlockType blockType, double xPos, double yPos);
    void connect(int sourceBlockID, std::string sourcePinName, int sinkBlockID, std::string sinkPinName);
    void moveBlock(int blockIndex, double xPos, double yPos);
    std::pair<double, double> blockPos(int blockIndex);
    std::unordered_map<int, Block> blocks;
protected:
    int currentIndex = 0;
};

#endif // FLOWCHART_H
