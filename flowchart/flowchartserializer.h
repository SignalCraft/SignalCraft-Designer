#ifndef FLOWCHARTSERIALIZER_H
#define FLOWCHARTSERIALIZER_H

#include <QMap>
#include <QString>
#include "flowchart/blocktype.h"
#include "flowchart/flowchart.h"
#include "flowchart/block.h"
#include "json/json.h"
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <boost/functional/hash/hash.hpp>

class FlowChartSerializer
{
public:
    FlowChartSerializer(QMap<QString, BlockType> blockTypes);
    FlowChart jsonParseFlowChart(Json::Value node);
    Json::Value jsonComposeFlowChart(FlowChart b);
protected:
    std::unordered_map<int, Block> jsonParseBlocks(Json::Value node);
    Json::Value jsonComposeBlocks(std::unordered_map<int, Block> map);
    Block jsonParseBlock(Json::Value node);
    Json::Value jsonComposeBlock(Block b);
    std::unordered_map<std::string, BlockPin> jsonParseInputConnections(Json::Value node);
    Json::Value jsonComposeInputConnections(std::unordered_map<std::string, BlockPin> map);
    BlockPin jsonParseBlockPin(Json::Value node);
    Json::Value jsonComposeBlockPin(BlockPin p);
    std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > jsonParseOutputConnections(Json::Value node);
    Json::Value jsonComposeOutputConnections(std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > map);
    std::unordered_set<BlockPin, boost::hash<BlockPin> > jsonParseBlockPinSet(Json::Value node);
    Json::Value jsonComposeBlockPinSet(std::unordered_set<BlockPin, boost::hash<BlockPin> > set);
    QMap<QString, BlockType> m_blockTypes;
};

#endif // FLOWCHARTSERIALIZER_H
