#ifndef BLOCK_H
#define BLOCK_H

#include <flowchart/blocktype.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "boost/functional/hash/hash.hpp"

typedef std::pair<int, std::string> BlockPin;

class Block
{
public:
    Block();
    Block(BlockType _blockType, double _xPos, double _yPos);
    void connectOutput(std::string outputPinName, BlockPin inputPin);
    void connectInput(std::string inputPinName, BlockPin outputPin);
    double xPos;
    double yPos;
    BlockType blockType;
    std::unordered_map<std::string, BlockPin> inputConnections;
    std::unordered_map<std::string, std::unordered_set<BlockPin, boost::hash<BlockPin>> > outputConnections;
};

#endif // BLOCK_H
