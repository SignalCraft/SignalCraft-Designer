#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <vector>
#include <string>

class BlockType
{
public:
    BlockType();
    std::string name;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs; 
};

#endif // BLOCKTYPE_H
