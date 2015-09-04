#include "flowchartserializer.h"

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

std::unordered_map<int, Block> FlowChartSerializer::jsonParseBlocks(Json::Value node) {
    std::unordered_map<int, Block> map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[itr.key().asInt()] = FlowChartSerializer::jsonParseBlock(*itr);
    }
    return map;
}

Json::Value FlowChartSerializer::jsonComposeBlocks(std::unordered_map<int, Block> map) {
    Json::Value node(Json::objectValue);
    for (auto kvpair : map) {
        node[std::to_string(kvpair.first)] = FlowChartSerializer::jsonComposeBlock(kvpair.second);
    }
    return node;
}

Block FlowChartSerializer::jsonParseBlock(Json::Value node) {
    Block b;
    b.blockType = m_blockTypes[QString::fromStdString(node["blockTypeName"].asString())];
    b.xPos = node["xPos"].asDouble();
    b.yPos = node["yPos"].asDouble();
    b.inputConnections = jsonParseInputConnections(node["inputConnections"]);
    b.outputConnections = jsonParseOutputConnections(node["outputConnections"]);
    return b;
}

Json::Value FlowChartSerializer::jsonComposeBlock(Block b) {
    Json::Value node(Json::objectValue);
    node["blockTypeName"] = b.blockType.name.toStdString();
    node["xPos"] = b.xPos;
    node["yPos"] = b.yPos;
    node["inputConnections"] = jsonComposeInputConnections(b.inputConnections);
    node["outputConnections"] = jsonComposeOutputConnections(b.outputConnections);
    return node;
}

std::unordered_map<std::string, BlockPin> FlowChartSerializer::jsonParseInputConnections(Json::Value node) {
    std::unordered_map<std::string, BlockPin> map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[itr.key().asString()] = jsonParseBlockPin(*itr);
    }
    return map;
}

Json::Value FlowChartSerializer::jsonComposeInputConnections(std::unordered_map<std::string, BlockPin> map) {
    Json::Value node(Json::objectValue);
    for (auto kvpair : map) {
        node[kvpair.first] = jsonComposeBlockPin(kvpair.second);
    }
    return node;
}

BlockPin FlowChartSerializer::jsonParseBlockPin(Json::Value node) {
    BlockPin p;
    p.first = node[0].asInt();
    p.second = node[1].asString();
    return p;
}

Json::Value FlowChartSerializer::jsonComposeBlockPin(BlockPin p) {
    Json::Value node(Json::arrayValue);
    node[0] = p.first;
    node[1] = p.second;
    return node;
}

std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > FlowChartSerializer::jsonParseOutputConnections(Json::Value node) {
    std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[itr.key().asString()] = jsonParseBlockPinSet(*itr);
    }
    return map;
}

Json::Value FlowChartSerializer::jsonComposeOutputConnections(std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > map) {
    Json::Value node(Json::objectValue);
    for (auto kvpair : map) {
        node[kvpair.first] = jsonComposeBlockPinSet(kvpair.second);
    }
    return node;
}

std::unordered_set<BlockPin, boost::hash<BlockPin> > FlowChartSerializer::jsonParseBlockPinSet(Json::Value node) {
    std::unordered_set<BlockPin, boost::hash<BlockPin> > set;
    for (unsigned int i=0; i < node.size(); i++) {
        set.insert(jsonParseBlockPin(node[i]));
    }
    return set;
}

Json::Value FlowChartSerializer::jsonComposeBlockPinSet(std::unordered_set<BlockPin, boost::hash<BlockPin> > set) {
    Json::Value node(Json::arrayValue);
    int i = 0;
    for (auto element : set) {
        node[i] = jsonComposeBlockPin(element);
        i++;
    }
    return node;
}
