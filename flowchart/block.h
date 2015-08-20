#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "boost/functional/hash/hash.hpp"
#include "json/json.h"

typedef std::pair<int, std::string> BlockPin;

class Block
{
public:
    Block();
    Block(std::string blockTypeName, double _xPos, double _yPos);
    void connectOutput(std::string outputPinName, BlockPin inputPin);
    void connectInput(std::string inputPinName, BlockPin outputPin);
    double xPos;
    double yPos;
    std::string blockTypeName;
    std::unordered_map<std::string, BlockPin> inputConnections;
    std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin>> > outputConnections;
    static Block jsonParseBlock(Json::Value node);
    static Json::Value jsonComposeBlock(Block b);
    static std::unordered_map<std::string, BlockPin> jsonParseInputConnections(Json::Value node);
    static Json::Value jsonComposeInputConnections(std::unordered_map<std::string, BlockPin> map);
    static BlockPin jsonParseBlockPin(Json::Value node);
    static Json::Value jsonComposeBlockPin(BlockPin p);
    static std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > jsonParseOutputConnections(Json::Value node);
    static Json::Value jsonComposeOutputConnections(std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin> > > map);
    static std::unordered_set<BlockPin, boost::hash<BlockPin> > jsonParseBlockPinSet(Json::Value node);
    static Json::Value jsonComposeBlockPinSet(std::unordered_set<BlockPin, boost::hash<BlockPin> > set);
};

#endif // BLOCK_H
