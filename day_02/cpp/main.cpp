#include <iostream>
#include <fstream>
#include <vector>
#include <map>

uint32_t part1();
uint32_t part2();

std::string inputFile = "../input/input.txt";
/* std::string inputFile = "../input/part1-test.txt"; */

int main()
{
  std::cout << "part1: " << part1() << std::endl;
  std::cout << "part2: " << part2() << std::endl;

}

uint32_t part1()
{
  std::ifstream file(inputFile);
  std::map<std::string, uint32_t> directions;
  uint32_t result = 0;

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return result;
  }

  std::string line;
  std::string temp;
  bool direction = true;

  while(file >> line)
  {
    if(direction)
    {
      temp = line;
      direction = false;
    }
    else
    {
      directions[temp] += stoi(line);
      direction = true;
    }
  }

  result = directions["forward"] * (directions["down"] - directions["up"]);

  return result;
}

uint32_t part2()
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return 0;
  }

  std::string line;
  std::string temp;
  bool direction = true;
  uint32_t aim = 0;
  uint32_t horizontal = 0;
  uint32_t depth = 0;

  while(file >> line)
  {
    if(direction)
    {
      temp = line;
      direction = false;
    }
    else
    {
      if(temp == "forward")
      {
        horizontal += stoi(line);
        depth += aim * stoi(line);
      }
      else if(temp == "down")
      {
        aim += stoi(line);
      }
      else
      {
        aim -= stoi(line);
      }
      direction = true;
    }
  }

  return horizontal * depth;
}
