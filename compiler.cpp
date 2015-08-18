#include <fstream>
#include <iostream>
#include <deque>


int writeFile(string picCode)
{
  std::ofstream filestream("filename.c")
  if(!filestream)
  {
   std::cerr<<"Cannot write to output file."<<::endl;
   return 1;
  }
  filestream<<picCode;
  filestream.close();
  return 0;
}

string generatePicCode(FlowChart flow)
{
  string includes;
  string main = "int main() {";
  std::set<int> expanded;
  std::deque<int> toBeExpanded;
  for(auto element : flow.blocks)
  { 
    int i = element.first;
    Block block =  element.second;
    if(block.inputConnections.empty())
    {
      blockIndexes.push_back(i);
    }
    includes<<"#include \""block.blockTypeName<<"\"\n";
  }
  while(!toBeExpanded.empty())
  {
    int blockIndex = toBeExpanded.pop_front();
    Block block = flow.blocks[blockIndex];
    bool found_all = true;
    for(auto input : block.inputConnections)
    {
      int blockNum = input.second.first;
      if(toBeExpanded.find(blockNum) == toBeExpanded.end())
      { 
        found_all = false;
        break;
      }   
    }
    if(found_all)
    {
      expand(block);
    }
    else
    {
      toBeExpanded.push_back(blockIndex);
    } 
 }
 
 
