#ifndef COMPILER_H
#define COMPILER_H

#include "flowchart/flowchart.h"
#include "flowchart/block.h"

#include <string>
#include <deque>
#include <set>

std::string generatePicCode(FlowChart flow);
bool isExpandable(Block block, std::set<int> toBeExpanded);
std::tuple<std::string, std::deque<int>, std::set<int>> expand(int blockIndex, FlowChart flow, std::deque<int> toBeExpanded, std::set<int> expanded, std::string mainFile);

#endif // COMPILER_H

