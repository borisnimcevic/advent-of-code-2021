#include <bits/stdint-uintn.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
  std::ifstream file("../input/part1.txt");
  /* std::ifstream file("../input/part1-test.txt"); */

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return 1;
  }

  std::vector<uint32_t> inputNumbers;

  std::string numberString;

  while(std::getline(file, numberString))
  {
    if(numberString.size() > 0)
    {
      inputNumbers.push_back(std::stoi(numberString));
    }
  }

  uint32_t increasingCounter = 0;

  for(auto i = 0; i < inputNumbers.size() - 3; ++i)
  {
    int a = 0;
    int b = 0;
    a = inputNumbers[i] + inputNumbers[i+1] + inputNumbers [i+2];
    b = inputNumbers[i + 1] + inputNumbers[i+2] + inputNumbers [i+3];
    if(a < b)
    {
      increasingCounter++;
    }
  }

  /* for (auto i : inputNumbers) { */
  /*   std::cout << i << std::endl; */
  /* } */

  std::cout << "size of the vector " <<  inputNumbers.size() << "\n";
  std::cout << "Number of the distance incremented: " <<  increasingCounter << "\n";
}
