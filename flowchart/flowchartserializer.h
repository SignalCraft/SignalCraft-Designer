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
#include "flowchart/blockpin.h"

/**
 * The FlowChartSerializer class handles JSON serialization and deserialization
 * of a FlowChart.
 */
class FlowChartSerializer {
public:
    /**
     * Construct a FlowChartSerializer.
     * @param blockTypes An ordered mapping of block type names to BlockTypes.
     */
    FlowChartSerializer(QMap<QString, BlockType> blockTypes);

    /**
     * Deserialize a JSON-encoded FlowChart.
     * @param node the JSON root node of the encoded FlowChart
     * @return the deserialized FlowChart
     */
    FlowChart jsonParseFlowChart(Json::Value node);

    /**
     * Serialize a FlowChart as JSON
     * @param b the FlowChart to serialize
     * @return the JSON serialization of the FlowChart
     */
    Json::Value jsonComposeFlowChart(FlowChart b);

private:
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
