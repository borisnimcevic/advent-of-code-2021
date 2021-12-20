#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void part1();
void printImage(const std::vector<std::vector<bool>> &);
void printLine(const std::vector<bool> &);
void getInput(std::vector<bool> &,std::vector<std::vector<bool>> &);
void applyFilter(const std::vector<bool> &,std::vector<std::vector<bool>> &);
int countLights(const std::vector<std::vector<bool>> &);
std::vector<std::vector<bool>> createBlankOutput(std::vector<std::vector<bool>> &);
std::vector<std::vector<bool>> addBorder(std::vector<std::vector<bool>> &input, int thickness, bool);
void flipBorder(std::vector<std::vector<bool>> &);


const std::string inputFile = "../input/old.input.txt";
/* const std::string inputFile = "../input/input.txt"; */
/* const std::string inputFile = "../input/test.txt"; */

int main()
{
  part1();
}

void part1()
{
  std::vector<bool> filter;
  std::vector<std::vector<bool>> input_image;
  getInput(filter, input_image);
  input_image = addBorder(input_image, 2, 1);

  for(int i = 0 ; i < 2; ++i)
  {
    std::cout << "before filter\n";
    /* printImage(input_image); */
    applyFilter(filter, input_image);
    flipBorder(input_image);
    std::cout << "after filter\n";
    /* printImage(input_image); */
    input_image = addBorder(input_image, 1, i % 2);
  }
  /* flipBorder(input_image); */

  /* printImage(input_image); */
  int lights = countLights(input_image);
  /* lights = lights - (2*input_image.size() + 2*input_image.front().size()); */
  std::cout << lights << "\n";

}

void printImage(const std::vector<std::vector<bool>> &image)
{
  /* std::cout << "image:\n"; */
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
  std::cout << "\n";
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

std::vector<std::vector<bool>> addBorder(std::vector<std::vector<bool>> &input, int thickness, bool odd)
{
  std::vector<bool> border;
  std::vector<bool> row_temp;
  std::vector<std::vector<bool>> temp_image;

  // top border
  const int width = input.front().size();
  for(int i = 0; i < width + (thickness*2); ++i)
  {
    border.push_back(false ^ !odd);
  }
  for(int i = 0; i < thickness; i++)
  {
    temp_image.push_back(border);
  }

  for(const auto &row: input)
  {
    row_temp.clear();
    for(int i = 0; i < thickness; i++)
    {
      row_temp.push_back(false ^ !odd);
    }
    for(const auto &p: row)
    {
      row_temp.push_back(p);
    }

    for(int i = 0; i < thickness; i++)
    {
      row_temp.push_back(false ^ !odd);
    }
    temp_image.push_back(row_temp);
  }
  for(int i = 0; i < thickness; i++)
  {
    temp_image.push_back(border);
  }

  return temp_image;
}

void applyFilter(const std::vector<bool> &filter ,std::vector<std::vector<bool>> &input)
{
  /* printImage(input); */
  std::vector<std::vector<bool>> output_image = createBlankOutput(input);

  std::vector<bool> index;

  for(int row = 1; row < input.size() - 1; row++)
  {
    for(int col = 1; col < input.front().size() - 1; col++)
    {
      index.clear();
      index.push_back(input.at(row-1).at(col-1));
      index.push_back(input.at(row-1).at(col));
      index.push_back(input.at(row-1).at(col+1));
      index.push_back(input.at(row).at(col-1));
      index.push_back(input.at(row).at(col));
      index.push_back(input.at(row).at(col+1));
      index.push_back(input.at(row+1).at(col-1));
      index.push_back(input.at(row+1).at(col));
      index.push_back(input.at(row+1).at(col+1));

      int num = 0;
      for(const auto &a: index)
      {
        num <<= 1;
        num |= a;
      }

      output_image.at(row).at(col) = filter.at(num);
    }
  }

  input = output_image;
  /* printImage(input); */
}

int countLights(const std::vector<std::vector<bool>> &input)
{
  int sum = 0;
  for(int row = 2; row < input.size() - 2; ++row)
  {
    for(int col = 2; col < input.front().size() - 2; ++col)
    {
        if(input.at(row).at(col))
          sum++;
    }
  }
  /* for(const auto &row: input) */
  /* { */
  /*   for(const auto &pixel: row) */
  /*   { */
  /*     if(pixel) */
  /*       sum++; */
  /*   } */
  /* } */
  return sum;
}

void flipBorder(std::vector<std::vector<bool>> &input)
{
  for(int i = 0; i < input.front().size(); i++)
  {
    input.front().at(i) = !input.front().at(i);
    input.back().at(i) = !input.back().at(i);
  }

  for(int row = 1; row < input.size() - 1; row++)
  {
    input.at(row).front() = !input.at(row).front();
    input.at(row).back() = !input.at(row).back();
  }
}

// 4942 is too high
