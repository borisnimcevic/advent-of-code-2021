#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>

void getData(std::vector<std::string> &);
void clearCorrupted(std::vector<std::string> &input);

uint64_t part1(const std::vector<std::string> &input);
uint64_t part2(const std::vector<std::string> &input);

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

int main()
{
  std::vector<std::string> input;
  getData(input);
  std::cout << part1(input) <<  " <<<<< part1" << std::endl;
  clearCorrupted(input);
  std::cout << part2(input) <<  " <<<<< part2" << std::endl;
}

void getData(std::vector<std::string> &input)
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string temp;

  while(file >> temp)
  {
    input.push_back(temp);
  }
}

void clearCorrupted(std::vector<std::string> &input)
{
  std::vector<char> brackets;
  std::vector<uint32_t> index;

  for(int i = 0; i < input.size(); ++i)
  {
    for(const auto &c : input.at(i))
    {
      if(c == '(' || c == '[' || c == '<' || c == '{')
      {
        brackets.push_back(c);
      }
      else
      {
        if(brackets.back() == c -1 || brackets.back() == c -2)
        {
          brackets.pop_back();
        }
        else
        {
          index.push_back(i);
          break;
        }
      }
    }
  }

  std::reverse(index.begin(),index.end());

  for(const auto i : index)
  {
    input.erase(input.begin()+i);
  }

}

uint64_t part1(const std::vector<std::string> &input)
{
  std::vector<char> brackets;
  std::map<char, uint32_t> points;

  for(const auto &line : input)
  {
    for(const auto &c : line)
    {
      if(c == '(' || c == '[' || c == '<' || c == '{')
      {
        brackets.push_back(c);
      }
      else
      {
        if(brackets.back() == c -1 || brackets.back() == c -2)
        {
          brackets.pop_back();
        }
        else
        {
          points[c]++;
          break;
        }
      }
    }
  }

  return points[')'] * 3 + points[']'] * 57 + points['}'] * 1197 + points['>'] * 25137;
}

uint64_t part2(const std::vector<std::string> &input)
{
  std::vector<uint64_t> nums;

  for(const auto &line : input)
  {
    std::vector<char> brackets;
    uint64_t points = 0;
    for(const auto &c : line)
    {
      if(c == '(' || c == '[' || c == '<' || c == '{')
      {
        brackets.push_back(c);
      }
      else
      {
        brackets.pop_back();
      }
    }

    while(brackets.begin() != brackets.end())
    {
      const auto c = brackets.back();
      points *= 5;
      if(c == '(')
        points+=1;
      if(c == '[')
        points+=2;
      if(c == '{')
        points+=3;
      if(c == '<')
        points+=4;
      brackets.pop_back();
    }
    nums.push_back(points);
  }

  std::sort(nums.begin(), nums.end());

  return nums.at(nums.size()/2);
}
