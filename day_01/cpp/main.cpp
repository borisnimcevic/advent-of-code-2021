#include <bits/stdint-uintn.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<uint32_t> readInput();
uint32_t part1(const std::vector<uint32_t> &);
uint32_t part2(const std::vector<uint32_t> &);

int main()
{
  std::vector<uint32_t> depths = readInput();

  if(depths.size() == 0){
    return 1;
  }

  std::cout << "Part 1 answer: " << part1(depths) << "\n";

  std::cout << "Part 2 answer: " << part2(depths) << "\n";
}

std::vector<uint32_t> readInput()
{

  std::ifstream file("../input/input.txt");
  std::vector<uint32_t> numbers;

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return numbers;
  }

  uint32_t number;

  while(file >> number)
  {
      numbers.push_back(number);
  }

  return numbers;
}

uint32_t part1(const std::vector<uint32_t> &depths)
{
  uint32_t numOfIncreadDepths = 0;

  for(auto index = 0; index < depths.size() - 1; ++index)
  {
    if(depths[index]  < depths[index+1])
    {
      numOfIncreadDepths++;
    }
  }
  return numOfIncreadDepths;
}

uint32_t part2(const std::vector<uint32_t> &depths)
{
  uint32_t numOfIncreadDepths = 0;

  for(auto index = 0; index < depths.size() - 3; ++index)
  {
    const auto lowerWindow = depths[index] + depths[index+1] + depths[index+2];
    const auto higherWindow = depths[index + 1] + depths[index+2] + depths[index+3];

    if(lowerWindow  < higherWindow)
    {
      numOfIncreadDepths++;
    }
  }

  return numOfIncreadDepths;
}
