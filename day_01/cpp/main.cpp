#include <bits/stdint-uintn.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
  std::ifstream file("../input/input.txt");

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return 1;
  }

  std::vector<uint32_t> depth;

  std::string depthString;

  while(std::getline(file, depthString))
  {
    if(depthString.size() > 0)
    {
      depth.push_back(std::stoi(depthString));
    }
  }

  uint32_t numOfIncreadDepths = 0;

  for(auto index = 0; index < depth.size() - 1; ++index)
  {
    if(depth[index]  < depth[index+1])
    {
      numOfIncreadDepths++;
    }
  }

  std::cout << "Part 1 answer: " << numOfIncreadDepths << "\n";

  numOfIncreadDepths = 0;

  for(auto index = 0; index < depth.size() - 3; ++index)
  {
    const auto lowerWindow = depth[index] + depth[index+1] + depth [index+2];
    const auto higherWindow = depth[index + 1] + depth[index+2] + depth [index+3];

    if(lowerWindow  < higherWindow)
    {
      numOfIncreadDepths++;
    }
  }

  std::cout << "Part 2 answer: " << numOfIncreadDepths << "\n";
}
