#include "flowchartserializer.h"

#include <QMap>
#include <QHash>
#include <QSet>
#include <QString>
#include <QPointF>
#include "json/json.h"
#include "flowchart/blocktype.h"
#include "flowchart/flowchart.h"
#include "flowchart/block.h"

FlowChartSerializer::FlowChartSerializer(QMap<QString, BlockType> blockTypes) {
    m_blockTypes = blockTypes;
}

FlowChart FlowChartSerializer::jsonParseFlowChart(Json::Value node) {
    FlowChart f;
    f.blocks = jsonParseBlocks(node["blocks"]);
    return f;
}

Json::Value FlowChartSerializer::jsonComposeFlowChart(FlowChart f) {
    Json::Value node(Json::objectValue);
    node["blocks"] = jsonComposeBlocks(f.blocks);
    return node;
}

QHash<int, Block> FlowChartSerializer::jsonParseBlocks(Json::Value node) {
    QHash<int, Block> map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[itr.key().asInt()] = FlowChartSerializer::jsonParseBlock(*itr);
    }
    return map;
}

Json::Value FlowChartSerializer::jsonComposeBlocks(QHash<int, Block> map) {
    Json::Value node(Json::objectValue);
    for (int key : map.keys()) {
        Block value = map[key];
        node[key] = FlowChartSerializer::jsonComposeBlock(value);
    }
    return node;
}

Block FlowChartSerializer::jsonParseBlock(Json::Value node) {
    BlockType blockType = m_blockTypes[QString::fromStdString(node["blockTypeName"].asString())];
    qreal xPos = node["xPos"].asDouble();
    qreal yPos = node["yPos"].asDouble();
    QPointF pos = QPointF(xPos, yPos);
    QHash<QString, BlockPin> inputConnections = jsonParseInputConnections(node["inputConnections"]);
    QHash< QString, QSet<BlockPin> > outputConnections = jsonParseOutputConnections(node["outputConnections"]);
    Block b(blockType, pos, inputConnections, outputConnections);
    return b;
}

Json::Value FlowChartSerializer::jsonComposeBlock(Block b) {
    Json::Value node(Json::objectValue);
    node["blockTypeName"] = b.blockType().name().toStdString();
    node["xPos"] = b.pos().x();
    node["yPos"] = b.pos().y();
    node["inputConnections"] = jsonComposeInputConnections(b.inputConnections());
    node["outputConnections"] = jsonComposeOutputConnections(b.outputConnections());
    return node;
}

QHash<QString, BlockPin> FlowChartSerializer::jsonParseInputConnections(Json::Value node) {
    QHash<QString, BlockPin> map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[QString::fromStdString(itr.key().asString())] = jsonParseBlockPin(*itr);
    }
    return map;
}

Json::Value FlowChartSerializer::jsonComposeInputConnections(QHash<QString, BlockPin> map) {
    Json::Value node(Json::objectValue);
    for (QString key : map.keys()) {
        BlockPin value = map[key];
        node[key.toStdString()] = jsonComposeBlockPin(value);
    }
    return node;
}

BlockPin FlowChartSerializer::jsonParseBlockPin(Json::Value node) {
    BlockPin p(node[0].asInt(), QString::fromStdString(node[1].asString()));
    return p;
}

Json::Value FlowChartSerializer::jsonComposeBlockPin(BlockPin p) {
    Json::Value node(Json::arrayValue);
    node[0] = p.blockNum();
    node[1] = p.pinName().toStdString();
    return node;
}

QHash<QString, QSet<BlockPin > > FlowChartSerializer::jsonParseOutputConnections(Json::Value node) {
    QHash<QString, QSet<BlockPin > > map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[QString::fromStdString(itr.key().asString())] = jsonParseBlockPinSet(*itr);
    }
    return map;
}

Json::Value FlowChartSerializer::jsonComposeOutputConnections(QHash<QString, QSet<BlockPin> > map) {
    Json::Value node(Json::objectValue);
    for (QString key : map.keys()) {
        auto value = map[key];
        node[key.toStdString()] = jsonComposeBlockPinSet(value);
    }
    return node;
}

QSet<BlockPin> FlowChartSerializer::jsonParseBlockPinSet(Json::Value node) {
    QSet<BlockPin > set;
    for (unsigned int i=0; i < node.size(); i++) {
        set.insert(jsonParseBlockPin(node[i]));
    }
    return set;
}

Json::Value FlowChartSerializer::jsonComposeBlockPinSet(QSet<BlockPin> set) {
    Json::Value node(Json::arrayValue);
    int i = 0;
    for (BlockPin element : set) {
        node[i] = jsonComposeBlockPin(element);
        i++;
    }
    return node;
}
