#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>

void part1(std::vector<std::vector<bool>> &);
void part2(std::vector<std::vector<bool>> &);

const std::string inputFile = "../input/input.txt";
const uint32_t LOOP = 793;
const uint32_t LOOP2 = 12;
/* const std::string inputFile = "../input/test.txt"; */
/* const uint32_t LOOP = 18; */
/* const uint32_t LOOP2 = 2; */

int main()
{
  std::vector<std::vector<bool>> field;
  part1(field);
  part2(field);
}


void printField(const std::vector<std::vector<bool>> &field)
{
  for(const auto &row : field)
  {
    for(const auto &col : row)
    {
      if(col)
        std::cout << "#";
      else
        std::cout << ".";
    }
    std::cout << "\n";
  }
}

void part1(std::vector<std::vector<bool>> &field)
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string temp;

  uint32_t maxX = 0;
  uint32_t maxY = 0;
  std::vector<uint32_t> tempNums;

  for(int i = 0; i < LOOP; ++i)
  {
    uint32_t tempX, tempY;
    file >> tempX;
    file >> tempY;
    tempNums.push_back(tempX);
    tempNums.push_back(tempY);

    if(tempX > maxX)
      maxX = tempX;
    if(tempY > maxY)
      maxY = tempY;
  }

  field.resize(maxY+1);
  for(int i = 0; i < field.size(); ++i)
  {
    field.at(i).resize(maxX+1, false);
  }

  for(int i = 1; i < tempNums.size() ; i=i+2)
  {
    uint32_t x,y;
    x = tempNums.at(i-1);
    y = tempNums.at(i);
    field.at(y).at(x) = true;
  }


  // first fold
  std::string tempAx;
  file >> tempAx;
  uint32_t fold;
  file >> fold;

  if(tempAx == "x")
  {
    for(int row = 0; row < field.size(); ++row)
    {
      for(int col = fold+1; col < field.at(0).size(); ++col)
      {
        if(field.at(row).at(col))
        field.at(row).at(fold-(col-fold)) = true;
      }
    }

    //clear right
    for(int row = 0; row < field.size(); ++row)
    {
      const auto popSize = field.at(row).size() - fold;
      for(int i = 0; i< popSize; ++i)
      {
        field.at(row).pop_back();
      }
    }

  }
  else
  {
    for(int row = fold+1; row < field.size(); ++row)
    {
      for(int col = 0; col < field.at(0).size(); ++col)
      {
        if(field.at(row).at(col))
        field.at(fold-(row-fold)).at(col) = true;
      }
    }

    //clear bottom
    const auto popSize = field.size() - fold;
    for(int i = 0; i < popSize; ++i)
    {
      field.pop_back();
    }

  }

  uint32_t hit = 0;
  for(const auto &row: field)
  {
    for(const auto col: row)
    {
      if(col)
        hit++;
    }
  }

  std::cout << "part1:\n" << hit <<  "\n";
}

void part2(std::vector<std::vector<bool>> &field)
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string temp;

  uint32_t maxX = 0;
  uint32_t maxY = 0;
  std::vector<uint32_t> tempNums;

  for(int i = 0; i < LOOP; ++i)
  {
    uint32_t tempX, tempY;
    file >> tempX;
    file >> tempY;
    tempNums.push_back(tempX);
    tempNums.push_back(tempY);

    if(tempX > maxX)
      maxX = tempX;
    if(tempY > maxY)
      maxY = tempY;
  }

  field.resize(maxY+1);
  for(int i = 0; i < field.size(); ++i)
  {
    field.at(i).resize(maxX+1, false);
  }

  for(int i = 1; i < tempNums.size() ; i=i+2)
  {
    uint32_t x,y;
    x = tempNums.at(i-1);
    y = tempNums.at(i);
    field.at(y).at(x) = true;
  }

  for(int i = 0; i < LOOP2; ++i)
  {
    std::string tempAx;
    file >> tempAx;
    uint32_t fold;
    file >> fold;

    if(tempAx == "x")
    {
      for(int row = 0; row < field.size(); ++row)
      {
        for(int col = fold+1, i = 0; (col < field.at(0).size() &&  i < fold) ; ++i, ++col)
        {
          if(field.at(row).at(col))
          field.at(row).at(fold-(col-fold)) = true;
        }
      }

      //clear right

      for(int row = 0; row < field.size(); ++row)
      {
        int popSize = field.at(row).size() - fold;
        for(int i = 0; i< popSize; ++i)
        {
          field.at(row).pop_back();
        }
      }

    }
    else
    {
      for(int row = fold+1, i = 0; (row < field.size() && i < fold); ++i, ++row)
      {
        for(int col = 0; col < field.at(0).size(); ++col)
        {
          if(field.at(row).at(col))
          field.at(fold-(row-fold)).at(col) = true;
        }
      }

      //clear bottom
      int popSize = field.size() - fold;
      for(int i = 0; i < popSize; ++i)
      {
        field.pop_back();
      }
    }
  }

  std::cout << "part2:\n";
  printField(field);
}
