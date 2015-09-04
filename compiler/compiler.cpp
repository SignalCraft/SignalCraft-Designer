#include "compiler.h"

#include <string>
#include <fstream>
#include <iostream>
#include <deque>
#include <tuple>
#include <functional>
#include <algorithm>

using namespace std;

string generatePicCode(FlowChart flow)
{
  string includes;
  string mainFile = "int main() {\n";
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
    std::size_t already = includes.find(block.blockType.name.toStdString()+".h");
    if(already == std::string::npos){
        includes += "#include \"" + block.blockType.name.toStdString() + ".h\"\n";
    }
  }
  includes += "\n";
  while(!toBeExpanded.empty())
  {
    int blockIndex = toBeExpanded.front();
    toBeExpanded.pop_front();
    Block block = flow.blocks[blockIndex];
    bool found_all = isExpandable(block, expanded);
    if(found_all)
    {
       auto results = expand(blockIndex, flow, toBeExpanded, expanded, mainFile);
       mainFile = std::get<0>(results);
       toBeExpanded = std::get<1>(results);
       expanded = std::get<2>(results);
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

std::tuple<std::string, std::deque<int>, std::set<int>> expand(int blockIndex, FlowChart flow, std::deque<int> toBeExpanded, std::set<int> expanded, std::string mainFile)
{
   Block block = flow.blocks[blockIndex];
   for(auto output : block.outputConnections){
        mainFile += "int wire_" + output.first + "=0;\n";
   }
   string type = block.blockType.name.toStdString();
   std::transform(type.begin(), type.end(), type.begin(), ::tolower);
   mainFile += type + "(";
   expanded.insert(blockIndex);
   for(auto input : block.inputConnections){
       mainFile += "*wire_" + input.first + ",";
   }
   for(auto output : block.outputConnections)
   {
         mainFile += "*wire_"+ output.first + ",";
   }
   mainFile.pop_back();
   mainFile += ");\n";
   for(auto output : block.outputConnections)
   {
      for(auto element : output.second){
         int outIndex = element.first;
         Block out = flow.blocks[outIndex];

         if(isExpandable(out,expanded))
         {
            toBeExpanded.push_back(outIndex);
            expand(outIndex, flow, toBeExpanded, expanded, mainFile);
         }
      }
   }
   auto results = std::make_tuple(mainFile, toBeExpanded, expanded);
   return results;
}


