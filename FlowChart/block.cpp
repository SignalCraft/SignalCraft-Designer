#include "flowchart/block.h"

#include "json/json.h"

Block::Block() {}

Block::Block(std::string _blockTypeName, double _xPos, double _yPos) {
    blockTypeName = _blockTypeName;
    xPos = _xPos;
    yPos = _yPos;
}

void Block::connectOutput(std::string outputPinName, BlockPin inputPin) {
    outputConnections[outputPinName].insert(inputPin);
}

void Block::connectInput(std::string inputPinName, BlockPin outputPin) {
    inputConnections[inputPinName] = outputPin;
}

Block Block::jsonParseBlock(Json::Value node) {
    Block b;
    b.blockTypeName = node["blockTypeName"].asString();
    b.xPos = node["xPos"].asDouble();
    b.yPos = node["yPos"].asDouble();
    b.inputConnections = jsonParseInputConnections(node["inputConnections"]);
    b.outputConnections = jsonParseOutputConnections(node["outputConnections"]);
    return b;
}

Json::Value Block::jsonComposeBlock(Block b) {
    Json::Value node;
    node["blockTypeName"] = b.blockTypeName;
    node["xPos"] = b.xPos;
    node["yPos"] = b.yPos;
    node["inputConnections"] = jsonComposeInputConnections(b.inputConnections);
    node["outputConnections"] = jsonComposeOutputConnections(b.outputConnections);
    return node;
}

std::unordered_map<std::string, BlockPin> Block::jsonParseInputConnections(Json::Value node) {
    std::unordered_map<std::string, BlockPin> map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[itr.key().asString()] = jsonParseBlockPin(*itr);
    }
    return map;
}

Json::Value Block::jsonComposeInputConnections(std::unordered_map<std::string, BlockPin> map) {
    Json::Value node;
    for (auto kvpair : map) {
        node[kvpair.first] = jsonComposeBlockPin(kvpair.second);
    }
    return node;
}

BlockPin Block::jsonParseBlockPin(Json::Value node) {
    BlockPin p;
    p.first = node[0].asInt();
    p.second = node[1].asString();
    return p;
}

Json::Value Block::jsonComposeBlockPin(BlockPin p) {
    Json::Value node;
    node[0] = p.first;
    node[1] = p.second;
    return node;
}

std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > Block::jsonParseOutputConnections(Json::Value node) {
    std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > map;
    for( Json::ValueIterator itr = node.begin() ; itr != node.end() ; itr++ ) {
        map[itr.key().asString()] = jsonParseBlockPinSet(*itr);
    }
    return map;
}

Json::Value Block::jsonComposeOutputConnections(std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > map) {
    Json::Value node;
    for (auto kvpair : map) {
        node[kvpair.first] = jsonComposeBlockPinSet(kvpair.second);
    }
    return node;
}

std::unordered_set<BlockPin, boost::hash<BlockPin> > Block::jsonParseBlockPinSet(Json::Value node) {
    std::unordered_set<BlockPin, boost::hash<BlockPin> > set;
    for (int i=0; i < node.size(); i++) {
        set.insert(jsonParseBlockPin(node[i]));
    }
    return set;
}

Json::Value Block::jsonComposeBlockPinSet(std::unordered_set<BlockPin, boost::hash<BlockPin> > set) {
    Json::Value node;
    int i = 0;
    for (auto element : set) {
        node[i] = jsonComposeBlockPin(element);
        i++;
    }
    return node;
}
