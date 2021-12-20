#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void part1();
void printImage(const std::vector<std::vector<bool>> &);
void printLine(const std::vector<bool> &);
void getInput(std::vector<bool> &,std::vector<std::vector<bool>> &);
std::vector<std::vector<bool>> createBlankOutput(std::vector<std::vector<bool>> &);
std::vector<std::vector<bool>> addBorder(std::vector<std::vector<bool>> &);


/* const std::string inputFile = "../input/input.txt"; */
const std::string inputFile = "../input/test.txt";

int main()
{
  part1();
}

void part1()
{
  std::vector<bool> filter;
  std::vector<std::vector<bool>> input_image;
  getInput(filter, input_image);

  input_image = addBorder(input_image);
  printImage(input_image);

  std::vector<std::vector<bool>> output_image = createBlankOutput(input_image);

  printImage(output_image);

  // apply filter
/*   std::vector<bool> index; */

/*   for(int row = 0; row < input_image.size(); row++) */
/*   { */
/*     for(int col = 0; col < input_image.front().size(); col++) */
/*     { */
/*     } */
/*   } */
}

void printImage(const std::vector<std::vector<bool>> &image)
{
  std::cout << "image:\n";
  for(const auto &row: image)
  {
    for(const auto &pixel: row)
    {
      if(pixel)
      {
        std::cout << "#";
      }
      else
      {
        std::cout << ".";
      }
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

void getInput(std::vector<bool> &filter, std::vector<std::vector<bool>> &input)
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
    input.push_back(row_temp);
  }
}

std::vector<std::vector<bool>> createBlankOutput(std::vector<std::vector<bool>> &input)
{
  std::vector<std::vector<bool>> output_image;
  std::vector<bool> row_temp;
  const int width = input.front().size();
  const int height = input.size();

  for(int j = 0; j < width; ++j)
  {
    row_temp.push_back(false);
  }

  for(int i = 0; i< height; ++i)
  {
    output_image.push_back(row_temp);
  }
  return output_image;
}

std::vector<std::vector<bool>> addBorder(std::vector<std::vector<bool>> &input)
{
  std::vector<bool> border;
  std::vector<bool> row_temp;
  std::vector<std::vector<bool>> temp_image;

  // top border
  const int width = input.front().size();
  for(int i = 0; i < width + 4; ++i)
  {
    border.push_back(false);
  }
  temp_image.push_back(border);
  temp_image.push_back(border);

  for(const auto &row: input)
  {
    row_temp.clear();
    row_temp.push_back(false);
    row_temp.push_back(false);
    for(const auto &p: row)
    {
      row_temp.push_back(p);
    }
    row_temp.push_back(false);
    row_temp.push_back(false);
    temp_image.push_back(row_temp);
  }
  temp_image.push_back(border);
  temp_image.push_back(border);

  return temp_image;
}
