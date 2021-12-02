#include <iostream>
#include <fstream>
#include <vector>
#include <map>

uint32_t part1();
uint32_t part2();

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/part1-test.txt"; */

int main()
{
  std::cout << "part1: " << part1() << std::endl;
  std::cout << "part2: " << part2() << std::endl;

}

uint32_t part1()
{
  std::ifstream file(inputFile);
  std::map<std::string, uint32_t> directions;

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return 0;
  }

  std::string direction;
  uint32_t magnitude;

  while(file >> direction >> magnitude)
  {
      directions[direction] += magnitude;
  }

  return directions["forward"] * (directions["down"] - directions["up"]);
}

uint32_t part2()
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return 0;
  }

  std::string direction;
  uint32_t magnitude;
  uint32_t aim = 0;
  uint32_t horizontal = 0;
  uint32_t depth = 0;

  while(file >> direction >> magnitude)
  {
      if(direction == "forward")
      {
        horizontal += magnitude;
        depth += aim * magnitude;
      }
      else if(direction == "down")
      {
        aim += magnitude;
      }
      else
      {
        aim -= magnitude;
      }
      direction = true;
  }

  return horizontal * depth;
}
