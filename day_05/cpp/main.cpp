#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>

uint32_t part1();
uint32_t part2();

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

std::vector<std::vector<uint32_t>> coordinates;
std::vector<std::vector<uint32_t>> field;

enum points{
  x1,
  y1,
  x2,
  y2
};

int main()
{
  std::cout << part1() <<  " <<<<< part1" << std::endl;
  std::cout << part2() <<  " <<<<< part2" << std::endl;
}


uint32_t findMaxX(const std::vector<std::vector<uint32_t>> &coordinates)
{
  uint32_t max = 0;
  for (const auto line : coordinates)
  {
    if(line.at(x1) > max)
      max = line.at(x1);
    if(line.at(x2) > max)
      max = line.at(x2);
  }
  return max;
}

uint32_t findMaxY(const std::vector<std::vector<uint32_t>> &coordinates)
{
  uint32_t max = 0;
  for (const auto line : coordinates)
  {
    if(line.at(y1)> max)
      max = line[y1];
    if(line[y2] > max)
      max = line[y2];
  }
  return max;
}

void printCoordinates(const std::vector<std::vector<uint32_t>> &coordinates){
  for(const auto line : coordinates)
  {
    for(const auto number : line)
    {
      std::cout << number << ",";
    }
    std::cout << "\n";
  }
}

void printField(std::vector<std::vector<uint32_t>> field){
  for(const auto row : field)
  {
    for(const auto number : row)
    {
      std::cout << number << ",";
    }
    std::cout << "\n";
  }
}

void initField(std::vector<std::vector<uint32_t>> &field,const uint32_t Y,const uint32_t X){
  for(int i = 0; i<= Y; i++)
  {
    std::vector<uint32_t> row;
    for(int j = 0; j<= X; j++)
    {
      row.push_back(0);
    }
    field.push_back(row);
  }
}

uint32_t calculatePoints(std::vector<std::vector<uint32_t>> field){
  uint32_t points = 0;
  for(const auto row : field)
  {
    for(const auto number : row)
    {
      if(number > 1)
      {
        points++;
      }
    }
  }
  return points;
}

void printLine(const std::vector<uint32_t> &line)
{
  for(const auto number : line)
  {
    std::cout << number << ",";
  }
  std::cout << "\n";
}

bool getData(){
  // ------ read file
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return false;
  }

  std::string X;
  std::string arrow;
  std::string Y;

  while(!file.eof())
  {
    std::vector<uint32_t> line;
    file >> X;
    file >> arrow;
    file >> Y;

    uint32_t temp;
    std::stringstream xx(X);
    xx >> temp;
    line.push_back(temp);
    xx.ignore();
    xx >> temp;
    line.push_back(temp);

    std::stringstream yy(Y);
    yy >> temp;
    line.push_back(temp);
    yy.ignore();
    yy >> temp;
    line.push_back(temp);

    coordinates.push_back(line);
  }
  coordinates.pop_back();


  // ------ create an empty matrix

  const uint32_t maxX = findMaxX(coordinates);
  const uint32_t maxY = findMaxY(coordinates);

  initField(field, maxY, maxX);
  return true;
}

uint32_t  part1()
{

  getData();
  // ------ intput lines
  for(const auto line : coordinates){
    if(line[0] == line [2])
    {
      const uint32_t lower = line[1] < line[3] ? line[1] : line[3];
      const uint32_t upper = line[1] > line[3] ? line[1] : line[3];
      for(int col = lower; col <= upper; col++)
      {
        field.at(col).at(line.at(0))++;
      }
    }
    else if(line[1] == line [3])
    {
      const uint32_t lower = line[0] < line[2] ? line[0] : line[2];
      const uint32_t upper = line[0] > line[2] ? line[0] : line[2];
      for(int row = lower; row <= upper; row++)
      {
        field.at(line.at(1)).at(row)++;
      }
    }
  }

  return calculatePoints(field);
}


uint32_t part2()
{
  getData();

  // ------ intput lines
  for(const auto line : coordinates){
    if(line[0] == line [2])
    {
      const uint32_t lower = line[1] < line[3] ? line[1] : line[3];
      const uint32_t upper = line[1] > line[3] ? line[1] : line[3];
      for(int col = lower; col <= upper; col++)
      {
        field.at(col).at(line.at(0))++;
      }
    }
    else if(line[1] == line [3])
    {
      const uint32_t lower = line[0] < line[2] ? line[0] : line[2];
      const uint32_t upper = line[0] > line[2] ? line[0] : line[2];
      for(int row = lower; row <= upper; row++)
      {
        field.at(line.at(1)).at(row)++;
      }
    }
    else
    {
      const int Xdiff = line.at(2) - line.at(0);
      const int Ydiff = line.at(3) - line.at(1);
      if(Xdiff > 0 && Ydiff > 0)
      {
        for(int i = 0; i <= abs(Xdiff); i++)
        {
          field.at(line.at(1)+i).at(line.at(0)+i)++;
        }
      }
      else if(Xdiff > 0 && Ydiff < 0)
      {
        for(int i = 0; i <= abs(Xdiff); i++)
        {
          field.at(line.at(1)-i).at(line.at(0)+i)++;
        }
      }
      else if(Xdiff < 0 && Ydiff > 0)
      {
        for(int i = 0; i <= abs(Xdiff); i++)
        {
          field.at(line.at(1)+i).at(line.at(0)-i)++;
        }
      }
      else if(Xdiff < 0 && Ydiff < 0)
      {
        for(int i = 0; i <= abs(Xdiff); i++)
        {
          field.at(line.at(1)-i).at(line.at(0)-i)++;
        }
      }

    }
  }

  return calculatePoints(field);
}
