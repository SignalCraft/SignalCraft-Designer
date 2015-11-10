#ifndef COMPILER_H
#define COMPILER_H

#include "flowchart/flowchart.h"
#include "flowchart/block.h"

#include <string>
#include <deque>
#include <set>

std::string generatePicCode(const FlowChart flow);
bool isExpandable(const Block block, const std::unordered_set<int> toBeExpanded);
std::unordered_set<std::string> extractUniqueBlockNames(const FlowChart flow);
std::deque<int> extractInputBlocks(const FlowChart flow);
std::unordered_set<std::string> extractWireNames(const FlowChart flow);

#endif // COMPILER_H

