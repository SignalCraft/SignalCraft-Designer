#ifndef FLOWCHARTSERIALIZER_H
#define FLOWCHARTSERIALIZER_H

#include <QMap>
#include <QString>
#include "flowchart/blocktype.h"
#include "flowchart/flowchart.h"
#include "flowchart/block.h"
#include "json/json.h"
#include <QHash>
#include <QSet>

class FlowChartSerializer
{
public:
    FlowChartSerializer(QMap<QString, BlockType> blockTypes);
    FlowChart jsonParseFlowChart(Json::Value node);
    Json::Value jsonComposeFlowChart(FlowChart b);
protected:
    QHash<int, Block> jsonParseBlocks(Json::Value node);
    Json::Value jsonComposeBlocks(QHash<int, Block> map);
    Block jsonParseBlock(Json::Value node);
    Json::Value jsonComposeBlock(Block b);
    QHash<QString, BlockPin> jsonParseInputConnections(Json::Value node);
    Json::Value jsonComposeInputConnections(QHash<QString, BlockPin> map);
    BlockPin jsonParseBlockPin(Json::Value node);
    Json::Value jsonComposeBlockPin(BlockPin p);
    QHash<QString, QSet<BlockPin> > jsonParseOutputConnections(Json::Value node);
    Json::Value jsonComposeOutputConnections(QHash<QString, QSet<BlockPin> > map);
    QSet<BlockPin> jsonParseBlockPinSet(Json::Value node);
    Json::Value jsonComposeBlockPinSet(QSet<BlockPin> set);
    QMap<QString, BlockType> m_blockTypes;
};

#endif // FLOWCHARTSERIALIZER_H
