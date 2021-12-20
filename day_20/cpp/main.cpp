#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void part1();
void printImage(const std::vector<std::vector<bool>> &);
void printLine(const std::vector<bool> &);
void getInput();

std::vector<bool> filter;
std::vector<std::vector<bool>> input_image;

/* const std::string inputFile = "../input/input.txt"; */
const std::string inputFile = "../input/test.txt";

int main()
{
  part1();
}

void part1()
{
  getInput();
  printLine(filter);
  printImage(input_image);
}

void printImage(const std::vector<std::vector<bool>> &image)
{
  for(const auto &row: image)
  {
    for(const auto &pixel: row)
    {
      std::cout << pixel;
    }
    std::cout << "\n";
  }
}

void printLine(const std::vector<bool> &line)
{
  for(const auto &pixel: line)
  {
    std::cout << pixel;
  }
  std::cout << "\n";
}

void getInput()
{
  std::ifstream file(inputFile);
  std::map<std::string, uint32_t> directions;

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return;
  }

  std::string temp;

  file >> temp;

  for (const auto & c : temp) 
  {
    if(c == '#')
    {
      filter.push_back(true);
    }
    else
    {
      filter.push_back(false);
    }
  }

  while(file >> temp)
  {
    std::vector<bool> row_temp;
    for (const auto & c : temp) 
    {
      if(c == '#')
      {
        row_temp.push_back(true);
      }
      else
      {
        row_temp.push_back(false);
      }
    }
    input_image.push_back(row_temp);
  }
}
