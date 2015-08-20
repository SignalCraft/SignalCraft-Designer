#include "compiler.h"

#include <string>
#include <fstream>
#include <iostream>
#include <deque>

using namespace std;

string generatePicCode(FlowChart flow)
{
  string includes;
  string mainFile = "int main() {";
  std::set<int> expanded;
  std::deque<int> toBeExpanded;
  for(auto element : flow.blocks)
  { 
    int i = element.first;
    Block block =  element.second;
    if(block.inputConnections.empty())
    {
      toBeExpanded.push_back(i);
    }
    includes += "#include \"" + block.blockTypeName + "\"\n";
  }
  while(!toBeExpanded.empty())
  {
    int blockIndex = toBeExpanded.front();
    toBeExpanded.pop_front();
    Block block = flow.blocks[blockIndex];
    bool found_all = isExpandable(block, expanded);
    if(found_all)
    {
      expand(blockIndex, flow, toBeExpanded, expanded);
    }
    else
    {
      toBeExpanded.push_back(blockIndex);
    }
  }
  mainFile += "}";
  includes += mainFile;
  return includes;
}

bool isExpandable(Block block, std::set<int> expanded)
{
    bool found_all = true;
    for(auto input : block.inputConnections)
    {
      int blockNum = input.second.first;
      if(expanded.find(blockNum) == expanded.end())
      { 
        found_all = false;
        break;
      }   
    }
    return found_all; 
}
 
void expand(int blockIndex, FlowChart flow, std::deque<int> toBeExpanded, std::set<int> expanded)
{
   Block block = flow.blocks[blockIndex];
   expanded.insert(blockIndex);
   for(auto output : block.outputConnections)
   {
      for(auto element : output.second){
         int outIndex = element.first;
         Block out = flow.blocks[outIndex];
         if(isExpandable(out,expanded))
         {
           expand(outIndex, flow, toBeExpanded, expanded);
         }
      }
   }
}

