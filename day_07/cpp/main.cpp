#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>

uint32_t part1(std::vector<int> &);
uint64_t part2(std::vector<int> &);
void getData(std::vector<int> &);

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */



int main()
{
  std::vector<int> positions;
  getData(positions);
  std::cout << part1(positions) <<  " <<<<< part1" << std::endl;
  std::cout << part2(positions) <<  " <<<<< part2" << std::endl;
}

void getData(std::vector<int> &pos)
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string temp;
  file >> temp;

  std::stringstream ss(temp);
  for(int i; ss >> i;)
  {
    pos.push_back(i);
    if(ss.peek() == ',')
    {
      ss.ignore();
    }
  }
}

void printPositions(const std::vector<uint32_t> &pos)
{
  for(const auto &p : pos)
  {
    std::cout << p << ", ";
  }
  std::cout << "\n";
}

float getAverage(const std::vector<int> &pos)
{
  float sum = 0;
  for(const auto &p : pos)
  {
    sum += p;
  }
  return sum/pos.size();
}

uint32_t calculateFuel1(const std::vector<int> &pos, const int mean)
{
  uint32_t sum = 0;
  for(const auto &p : pos)
  {
    sum += abs(p - mean);
  }
  return sum;
}

uint32_t calculateFuel2(const std::vector<int> &pos, const int avg)
{
  uint32_t sum = 0;
  for(const auto &p : pos)
  {
    auto diff = abs(p - avg);
    for(int i = 0; i <= diff; i++){
      sum += i;
    }
  }
  return sum;
}

uint32_t  part1(std::vector<int> &positions)
{
  std::sort(positions.begin(), positions.end());
  const auto mean = positions.at(positions.size()/2);

  return calculateFuel1(positions, mean);
}


uint64_t part2(std::vector<int> &positions)
{
  const auto avg = floor(getAverage(positions));
  return calculateFuel2(positions, avg);
}
