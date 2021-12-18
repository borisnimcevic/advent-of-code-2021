#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>


/* const std::string inputFile = "../input/input.txt"; */
const std::string inputFile = "../input/test.txt";

const int INF = 999;

std::vector<std::vector<std::pair<int,std::pair<int,int>>>> input;

void getInput();

int main()
{
  getInput();
}

void getInput()
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
  }

  std::string row_temp;
  std::pair<int, int> nums_temp;
  std::pair<int, std::pair<int, int>> obj_temp;
  std::vector<std::pair<int, std::pair<int, int>>> entry_temp;
  int lvl_counter = 0;

  file >> row_temp;

  std::stringstream ss(row_temp);

  std::vector<char> char_stack;

  for (auto i : row_temp) 
  {
    if(i == ']')
    {
      lvl_counter--;
      if(char_stack.back() == ',')
      {
        if(char_stack.at(char_stack.size()-2) == '[')
        {
          char_stack.pop_back(); // remove comma
          char_stack.pop_back(); // remove open bracket
        }
        else
        {
          nums_temp.second = INF;
          char_stack.pop_back(); // remove comma
          nums_temp.first = char_stack.back() - '0';
          char_stack.pop_back(); // remove number
          char_stack.pop_back(); // remove open bracket
          obj_temp.first = lvl_counter;
          obj_temp.second.first = nums_temp.first;
          obj_temp.second.second = nums_temp.second;
          entry_temp.push_back(obj_temp);
        }
      }
      else
      {
        nums_temp.second = char_stack.back() - '0';
        char_stack.pop_back(); // pop number
        char_stack.pop_back(); // pop comma
        if(char_stack.back() == '[')
        {
          nums_temp.first = INF;
        }
        else
        {
          nums_temp.first = char_stack.back() - '0';
          char_stack.pop_back(); // pop number
        }
        char_stack.pop_back(); // pop open bracket
        obj_temp.first = lvl_counter;
        obj_temp.second.first = nums_temp.first;
        obj_temp.second.second = nums_temp.second;
        entry_temp.push_back(obj_temp);
      }
    }
    else if(i == '[')
    {
      lvl_counter++;
      char_stack.push_back(i);
    }
    else
    {
      char_stack.push_back(i);
    }
  }


  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << row_temp << std::endl;
  for (auto a : entry_temp) 
  {
    std::cout << "([" << a.first << "][" << a.second.first << "," << a.second.second << "]), ";
  }
  std::cout << std::endl;


}
