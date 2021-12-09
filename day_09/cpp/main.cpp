#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>

void getData(std::vector<std::vector<std::uint32_t>> &);
uint64_t part1(const std::vector<std::vector<std::uint32_t>> &);
uint64_t part2(const std::vector<std::vector<std::uint32_t>> &);

const std::string inputFile = "../input/input.txt";
const int LOOP_COUNT = 100;
/* const std::string inputFile = "../input/test.txt"; */
/* const int LOOP_COUNT = 10; */

int main()
{
  std::vector<std::vector<std::uint32_t>> digits;
  getData(digits);
  std::cout << part1(digits) <<  " <<<<< part1" << std::endl;
  std::cout << part2(digits) <<  " <<<<< part2" << std::endl;
}

void printInup(const std::vector<std::vector<std::uint32_t>> &digits)
{
  for(int i = 0; i < digits.size(); ++i)
  {
    for(int j = 0; j < digits.at(0).size(); ++j)
    {
      std::cout << digits.at(i).at(j) << ", ";
    }
    std::cout << "\n";
  }
}

std::vector<std::vector<uint32_t>> strip(const std::vector<std::vector<std::uint32_t>> &field)
{
  std::vector<std::vector<uint32_t>> temp;
  for(int i = 1; i < field.size() - 1; ++i)
  {
    std::vector<uint32_t> rowTemp;
    for(int j = 1; j < field.at(0).size() - 1; ++j)
    {
      rowTemp.push_back(field.at(i).at(j));
    }
    temp.push_back(rowTemp);
  }
  return temp;
}

void getData(std::vector<std::vector<std::uint32_t>> &digits)
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string temp;

  // make first border
  std::vector<std::uint32_t> row;
  for(int i = 0; i < LOOP_COUNT +2; ++i)
  {
    row.push_back(10);
  }
  digits.push_back(row);

  while(file >> temp)
  {
    row.clear();
    row.push_back(10);
    for(auto num : temp)
    {
      row.push_back(num-'0');
    }
    row.push_back(10);
    digits.push_back(row);
  }

  row.clear();
  for(int i = 0; i < temp.size()+2; ++i)
  {
    row.push_back(10);
  }
  digits.push_back(row);
}

uint64_t findMax(std::vector<uint32_t> &res)
{
  int max = 0;
  int maxIndex = 0;
  for(int i = 0; i < res.size(); ++i)
  {
    if(res.at(i) > max)
    {
      max = res.at(i);
      maxIndex = i;
    }
  }
  res.at(maxIndex) = 0;
  return max;
}

uint64_t part1(const std::vector<std::vector<std::uint32_t>> &digits)
{
  uint64_t sum = 0;

  for(int col = 1 ; col < digits.size() - 1; ++col)
  {
    for(int row = 1; row < digits.at(0).size() - 1; ++row)
    {
      int center = digits.at(col).at(row);
      if(center < digits.at(col).at(row+1))
      {
        if(center < digits.at(col).at(row-1))
        {
          if(center < digits.at(col+1).at(row))
          {
          if(center < digits.at(col-1).at(row))
            {
              sum+= center+1;
            }
          }
        }
      }
    }
  }

  return sum;
}

uint32_t countNum(const std::vector<std::vector<uint32_t>> &basin , const uint32_t target)
{
  uint32_t sum = 0;
  for(const auto &row : basin)
  {
    for(const auto num : row)
    {
      if(num == target)
      {
        sum++;
      }
    }
  }
  return sum;
}

bool cleanField(std::vector<std::vector<uint32_t>> &field)
{
  for(int col = 1 ; col < field.size() - 1; ++col)
  {
    for(int row = 1; row < field.at(0).size() - 1; ++row)
    {
      int current = field.at(col).at(row);
      if(current !=0)
      {
        if(field.at(col).at(row) < field.at(col+1).at(row))
        {
          if(field.at(col+1).at(row) != 0)
          {
            field.at(col).at(row) = field.at(col+1).at(row);
            return true;
          }
        }
        if(field.at(col).at(row) < field.at(col-1).at(row))
        {
          if(field.at(col-1).at(row) != 0)
          {
            field.at(col).at(row) = field.at(col-1).at(row);
            return true;
          }
        }
        if(field.at(col).at(row) < field.at(col).at(row+1))
        {
          if(field.at(col).at(row+1) != 0)
          {
            field.at(col).at(row) = field.at(col).at(row+1);
            return true;
          }
        }
        if(field.at(col).at(row) < field.at(col).at(row-1))
        {
          if(field.at(col).at(row-1) != 0)
          {
            field.at(col).at(row) = field.at(col).at(row-1);
            return true;
          }
        }
      }
    }
  }

  return false;
}

uint64_t part2(const std::vector<std::vector<std::uint32_t>> &digits)
{
  std::vector<std::vector<uint32_t>> field;
  std::vector<uint32_t> tempRow;
  tempRow.resize(digits.at(0).size(), 0);

  uint32_t counter = 0;

  for(int i = 0; i < digits.size(); ++i)
  {
    field.push_back(tempRow);
  }

  for(int col = 1 ; col < digits.size() - 1; ++col)
  {
    for(int row = 1; row < digits.at(0).size() - 1; ++row)
    {
      int center = digits.at(col).at(row);
      if(center != 9)
      {
        if(field.at(col-1).at(row) != 0)
        {
          field.at(col).at(row) = field.at(col-1).at(row);
        }
        else if(field.at(col).at(row-1) != 0)
        {
          field.at(col).at(row) = field.at(col).at(row-1);
        }
        else if(field.at(col).at(row+1) != 0)
        {
          field.at(col).at(row) = field.at(col).at(row+1);
        }
        else
        {
          counter++;
          field.at(col).at(row) = counter;
        }
        if(digits.at(col+1).at(row) != 9)
        {
          field.at(col+1).at(row) = field.at(col).at(row);
        }
        if(digits.at(col).at(row+1) != 9)
        {
          field.at(col).at(row+1) = field.at(col).at(row);
        }
        if(digits.at(col-1).at(row) != 9)
        {
          field.at(col-1).at(row) = field.at(col).at(row);
        }
        if(digits.at(col).at(row-1) != 9)
        {
          field.at(col).at(row-1) = field.at(col).at(row);
        }
      }
    }
  }


  bool notCleaned = true;
  while(notCleaned)
  {
    notCleaned = cleanField(field);
  }

  const std::vector<std::vector<uint32_t>> basin = strip(field);
  std::vector<uint32_t> result;
  result.resize(counter+1, 0);

  for(int i = 1; i < counter+1; ++i)
  {
    result[i] = countNum(basin, i);
  }

  uint64_t res = 1;
  for(int i = 0; i < 3; ++i)
  {
    res *= findMax(result);
  }

  return res;
}
