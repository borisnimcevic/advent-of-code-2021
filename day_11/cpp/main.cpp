#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>

void getData(std::vector<std::vector<int>> &);

void bothParts(std::vector<std::vector<int>> &);

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

int main()
{
  std::vector<std::vector<int>> input;
  getData(input);
  bothParts(input);
}

void printField(const std::vector<std::vector<int>> &input)
{
  for(int row = 1; row < input.size() - 1; ++row)
  {
    for(int col = 1; col < input.at(0).size() - 1; ++col)
    {
      printf("%2d, ", input.at(row).at(col));
    }
    std::cout << "\n";
  }
}

void getData(std::vector<std::vector<int>> &input)
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string temp;

  // make first border
  std::vector<int> row;
  for(int i = 0; i < 12; ++i)
  {
    row.push_back(-1);
  }
  input.push_back(row);

  while(file >> temp)
  {
    row.clear();
    row.push_back(-1);

    for(auto num : temp)
    {
      row.push_back(num-'0');
    }
    row.push_back(-1);
    input.push_back(row);
  }

  // make last border
  row.clear();
  for(int i = 0; i < 12; ++i)
  {
    row.push_back(-1);
  }
  input.push_back(row);
}


void bothParts(std::vector<std::vector<int>> &input)
{
  uint64_t flashNum = 0;
  uint32_t step = 0;
  bool sync = true;

  while(sync)
  {
    step++;
    // increase energy
    for(int row = 1; row < input.size() -1; ++row)
    {
      for(int col = 1; col < input.size() -1; ++col)
      {
        input.at(row).at(col)++;
      }
    }

    // explosions
    bool flashed = true;
    while(flashed)
    {
      flashed = false;
      for(int row = 1; row < input.size() -1; ++row)
      {
        for(int col = 1; col < input.size() -1; ++col)
        {
          if(input.at(row).at(col) > 9)
          {
            flashNum++;
            input.at(row).at(col) = 0;
            flashed = true;

            // left
            if(input.at(row).at(col-1) > 0)
              input.at(row).at(col-1)++;

            // left-up
            if(input.at(row-1).at(col-1) > 0)
              input.at(row-1).at(col-1)++;

            // up
            if(input.at(row-1).at(col) > 0)
              input.at(row-1).at(col)++;

            // right up
            if(input.at(row-1).at(col+1) > 0)
              input.at(row-1).at(col+1)++;

            // right
            if(input.at(row).at(col+1) > 0)
              input.at(row).at(col+1)++;

            // right down
            if(input.at(row+1).at(col+1) > 0)
              input.at(row+1).at(col+1)++;

            // down
            if(input.at(row+1).at(col) > 0)
              input.at(row+1).at(col)++;

            // left down
            if(input.at(row+1).at(col-1) > 0)
              input.at(row+1).at(col-1)++;
          }
        }
      }
    }

    for(int row = 1; row < input.size() -1; ++row)
    {
      for(int col = 1; col < input.size() -1; ++col)
      {
        if(input.at(row).at(col) != 0)
        {
          sync = false;
          break;
        }
      }
    }

    if(sync)
    {
      sync = false;
      std::cout << (int)step <<  " <<<<< part2" << std::endl;
    }
    else
    {
      sync = true;
    }

    if(step == 100)
    {
      std::cout << (int)flashNum <<  " <<<<< part1" << std::endl;
    }
  }
}
