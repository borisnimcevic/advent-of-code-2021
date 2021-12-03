#include <iostream>
#include <fstream>
#include <bitset>
#include <math.h>
#include <map>
#include <vector>

uint32_t part1();
uint32_t part2();

const std::string inputFile = "../input/input.txt";
/* const std::string inputFile = "../input/test.txt"; */

int main()
{
  std::cout << "part1: " << part1() << std::endl;
  std::cout << "part2: " << part2() << std::endl;
}

uint32_t  part1()
{
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return 0;
  }

  std::string binaryString;
  std::map<uint8_t,uint32_t> ones;
  std::map<uint8_t,uint32_t> zeros;

  while(file >> binaryString )
  {
    for(auto i = 0 ; i < binaryString.size() ; ++i)
    {
      const auto index = binaryString.size() - i - 1;
      if(binaryString[i] == '1')
      {
        ones[i]++;
      }
      else
      {
        zeros[i]++;
      }
    }
  }

  uint16_t delta = 0;
  uint16_t epsilon = 0;
  for(auto i = 0 ; i < binaryString.size() ; ++i)
  {
    if(ones[i] > zeros[i])
    {
      delta |= 1 << (binaryString.size() - i - 1);
    }
    else
    {
      epsilon |= 1 << (binaryString.size() - i - 1);
    }
  }

  return delta * epsilon;
}

uint16_t findOxygen(const std::vector<uint16_t> numbers, const int mask, const uint8_t size){

  if(numbers.size() == 1)
  {
    return numbers[0];
  }

  std::map<uint8_t,uint32_t> ones;
  std::map<uint8_t,uint32_t> zeros;

  for(auto number :numbers)
  {
    for(int i = 0; i < size ; ++i)
    {
      if(number & 1 << i)
      {
        ones[i]++;
      }
      else
      {
        zeros[i]++;
      }
    }
  }

  std::vector<uint16_t> newNumbers;
  if(ones[mask] >= zeros[mask])
  {
    for(auto number : numbers)
    {
      if(number & 1 << mask)
      {
        newNumbers.push_back(number);
      }
    }
  }
  else
  {
    for(auto number : numbers)
    {
      if(!(number & 1 << mask))
      {
        newNumbers.push_back(number);
      }
    }
  }

  return findOxygen(newNumbers, mask - 1, size);
}

uint16_t findCO2(const std::vector<uint16_t> numbers, const int mask, const uint8_t size){

  if(numbers.size() == 1 || mask<0)
  {
    return numbers[0];
  }

  std::map<uint8_t,uint32_t> ones;
  std::map<uint8_t,uint32_t> zeros;

  for(auto number :numbers)
  {
    for(int i = 0; i < size ; ++i)
    {
      if(number & 1 << i)
      {
        ones[i]++;
      }
      else
      {
        zeros[i]++;
      }
    }
  }

  std::vector<uint16_t> newNumbers;
  if(ones[mask] >= zeros[mask])
  {
    for(auto number : numbers)
    {
      if(!(number & 1 << mask))
      {
        newNumbers.push_back(number);
      }
    }
  }
  else
  {
    for(auto number : numbers)
    {
      if(number & 1 << mask)
      {
        newNumbers.push_back(number);
      }
    }
  }

  return findCO2(newNumbers, mask - 1, size);
}

uint32_t  part2()
{
  std::vector<uint16_t> numbers;
  std::ifstream file(inputFile);

  if(!file)
  {
    std::cerr<<"Cannot find the file."<< std::endl;
    return 0;
  }

  std::string binaryString;

  while(file >> binaryString )
  {
    uint16_t number = 0;
    for(auto i = 0 ; i < binaryString.size() ; ++i)
    {
      if(binaryString[i] == '1')
      {
        number+= pow(2, binaryString.size() - i - 1);
      }
    }
    numbers.push_back(number);
  }

  const uint16_t mask = binaryString.size() - 1;

  auto oxygen = findOxygen(numbers, mask, binaryString.size());
  auto co2 = findCO2(numbers, mask, binaryString.size());
  return oxygen * co2;
}
