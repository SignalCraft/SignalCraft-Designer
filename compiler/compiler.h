#ifndef COMPILER_H
#define COMPILER_H

#include "flowchart/flowchart.h"
#include "flowchart/block.h"

#include <string>
#include <deque>
#include <set>

std::string generatePicCode(FlowChart flow);
bool isExpandable(Block block, std::set<int> toBeExpanded);
void expand(int blockIndex, FlowChart flow, std::deque<int> toBeExpanded, std::set<int> expanded);

#endif // COMPILER_H

