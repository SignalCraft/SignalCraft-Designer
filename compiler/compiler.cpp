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
  string mainFile = "int main() {";
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
    bool found_all = isExpandable(block, toBeExpanded);
    if(found_all)
    {
      expand(block, toBeExpanded, expanded);  
    }
    else
    {
      toBeExpanded.push_back(blockIndex);
    }
  }
  mainFile<<"}";
  includes<<mainFile;
  return includes 
}

bool isExpandable(Block block, std::deque toBeExpanded)
{
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
    return found_all; 
}
 
void expand(int blockIndex, std::deque toBeExpanded, std::set expanded)
{
   Block block = flow.blocks[blockIndex]
   expanded.push_back(blockIndex);
   for(auto output : block.outputConnections)
   {
      if(isExpandable(output,toBeExpanded))
      {
        expand(block, toBeExpanded, expanded);  
      }
   }
}

int main()
{

} 
